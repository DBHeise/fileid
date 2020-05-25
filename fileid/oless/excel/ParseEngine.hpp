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

			Record* GetRecordOfType(unsigned short type, unsigned short idx) override {
				unsigned short currentIdx = 0;
				for (auto it = this->masterList.begin(); it != this->masterList.end(); it++)
				{
					Record* r = (*it);
					if (r->Type == type) {
						if (idx == currentIdx) {
							return r;
						}
						else {
							currentIdx++;
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
				unsigned short version = 0;
				unsigned int sheetIndex = 0;

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
					auto r = ParseRecord(recordType, data, version, this);
					if (r != nullptr) {
						switch (recordType)
						{
						case 0x0009://BOFRecord (BIFF2)
						case 0x0209://BOFRecord (BIFF3)
						case 0x0409://BOFRecord (BIFF4)
						case 0x0809://BOFRecord (BIFF5 and BIFF8)
						{
							if (index == 4) { //Global BOF
								BOFRecord* bofr = ((BOFRecord*)r);
								auto bof = bofr->GetRawBOF();
								this->Version = bof->vers;
								this->VersionName = GetVersion_Excel(bof->vers);
								this->SubType = this->VersionName;
								version = bof->vers;
							}
							else { //SubStream BOF
								if (version == (unsigned short)ExcelVersion::BIFF8) {
									if (lookup.count(index - 4) == 1) { //BIFF8
										auto idx = lookup[index - 4];
										if (idx >= 0) {
											currentSheet = &(this->sheets[idx]);
										}
									}
								}
								else if (version == (unsigned short)ExcelVersion::BIFF5) { //BIFF5
									if (currentSheet == nullptr) {
										sheetIndex = 0;
									} else {
										sheetIndex++;
									}
									if (sheetIndex < this->sheets.size()) {
										currentSheet = &(this->sheets[sheetIndex]);
									}
								}
								else {
									currentSheet = nullptr;
								}
							}
							break;
						}
						case 0x0085: //BoundSheet8Record
						{
							Sheet si;
							if (version == (unsigned short)ExcelVersion::BIFF8) {
								auto bs8r = (BoundSheet8Record*)r;
								auto header = bs8r->GetRawHeader();
								si.Name = bs8r->Name;
								si.Type = header->dt;
								si.Visiblity = header->hsState;
								si.Offset = header->lbPlyPos;
								lookup[si.Offset] = this->sheets.size();
							}
							else if (version == (unsigned short)ExcelVersion::BIFF5) {
								auto bs5r = (BoundSheet5Record*)r;
								si.Name = bs5r->Name;
							}

							this->sheets.push_back(si);
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
