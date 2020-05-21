#pragma once

#include "records/Record.hpp"

namespace oless {
	namespace excel {
		using namespace records;
		
		class ParseEngine : public IRecordParser {
		private:
			Sheet* currentSheet;
			std::map<unsigned int, int> lookup;
			unsigned int index;
			records::Record* lastRecord;
			std::vector<records::Record*> masterList;
		public:
			SubStream* global;
			std::vector<Sheet> sheets;
			std::string SubType;
			unsigned short Version;
			std::string VersionName;

		public:
			ParseEngine() {
				this->currentSheet = nullptr;
			}

			Record* GetPrevRecord() override {
				return this->lastRecord;
			}

			Record* GetPrevRecordOfType(unsigned short type) override {
				if (this->lastRecord->Type == type) {
					return this->lastRecord;
				}
				else {
					for (auto rit = this->masterList.rbegin(); rit != this->masterList.rend(); rit++)
					{
						Record* r = (*rit);
						if (r->Type == type) {
							return r;
						}
					}
				}
				return nullptr;
			}
			Record* GetPrevRecordNotOfType(unsigned short type) override {
				if (this->lastRecord->Type != type) {
					return this->lastRecord;
				}
				else {
					for (auto rit = this->masterList.rbegin(); rit != this->masterList.rend(); rit++)
					{
						Record* r = (*rit);
						if (r->Type != type) {
							return r;
						}
					}
				}
				return nullptr;
			}

			// ParseStream - parses a workbook stream
			void ParseStream(POLE::Stream* workbookStream) {
				this->index = 0;

				//TODO: ??more efficient way of reading the stream instead of pulling in the entire body-chunk...
				POLE::uint64 streamSize = workbookStream->size();
				unsigned char* buffer = new unsigned char[streamSize];
				memset(buffer, 0, streamSize);

				POLE::uint64 bytesRead = workbookStream->read(buffer, streamSize);

				if (bytesRead != streamSize) {
					//throw std::runtime_error("bytesRead != streamSize...how is this even possible!");
					//Likely corrupted or incomplete file
					this->global = nullptr;
					this->sheets.clear();
					this->SubType = "Corrupted";
					delete buffer;
					return;
				}

				this->global = new SubStream;

				while (this->index + 4 < streamSize)
				{
					unsigned short recordType = common::ReadUShort(buffer, streamSize, this->index);
					this->index += 2;
					unsigned short recordSize = common::ReadUShort(buffer, streamSize, this->index);
					this->index += 2;

					std::vector<uint8_t> data;
					if (this->index + recordSize < streamSize) {
						data.insert(data.end(), &buffer[this->index], &buffer[this->index + recordSize]);
					}
					auto r = ParseRecord(this, recordType, data);
					if (r != nullptr) {
						switch (recordType)
						{
						case 0x0809: //BOFRecord
						{
							if (index == 4) { //Global BOF
								auto bof = ((BOFRecord*)r)->GetRawBOF();
								this->Version = bof->vers;
								this->VersionName = GetVersion_Excel(bof->vers);
								this->SubType = this->VersionName;
							}
							else { //SubStream BOF
								if (lookup.count(index - 4) == 1) {
									currentSheet = &(this->sheets[lookup[index - 4]]);
								}
								else {
									//this case is where the BOF doesn't match the known sheets 
									// ...so we just add it to the global??
									currentSheet = nullptr;
								}
							}
							break;
						}
						case 0x0085: //BoundSheet8Record
						{
							Sheet si;
							auto header = ((BoundSheet8Record*)r)->GetRawHeader();
							si.Name = ((BoundSheet8Record*)r)->Name;
							si.Type = header->dt;
							si.Visiblity = header->hsState;
							si.Offset = header->lbPlyPos;

							this->sheets.push_back(si);
							lookup[si.Offset] = this->sheets.size() - 1;
							break;
						}
						case 0x002F: //FilePassRecord
							this->index += streamSize; //exit, we're not decrypting, so we won't be able to parse the rest correctly
							break;
						default:
							break;
						}

						if (this->currentSheet != nullptr) {
							this->currentSheet->AddRecord(r);
						}
						else {
							this->global->AddRecord(r);
						}

						this->lastRecord = r;
						this->masterList.push_back(r);
					}
					else {
						//insert error parsing record type record??
					}
					index += recordSize;
				}

				delete buffer;

			}
		};
	}
}
