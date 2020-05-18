#pragma once

#include <map>
#include "../pole.h"
#include "../../common.hpp"
#include "../OleCommon.hpp"
#include "MSExcel.common.hpp"
#include "MSExcel.formulas.hpp"
#include "SubStream.hpp"
#include "Sheet.hpp"
#include "records/Record.Parser.hpp"

namespace OleStructuredStorage {
	namespace Excel {

		using namespace OleStructuredStorage::Excel::Records;

		class ExcelExtensionInfo : public OLESSExtensionInfo {
		private:
			//Global SubStream
			SubStream* global;
			std::vector<Sheet> sheets;

		public:
			ExcelExtensionInfo() : OLESSExtensionInfo() {
				this->Extension = "xls";
				this->Name = "Microsoft Office Excel Workbook";
			}

			// ParseStream - parses a workbook stream
			void ParseStream(POLE::Stream* workbookStream) {

				std::map<unsigned int, int> lookup;

				//TODO: ??more efficient way of reading the stream instead of pulling in the entire body-chunk...

				POLE::uint64 streamSize = workbookStream->size();
				unsigned char* buffer = new unsigned char[streamSize];

				//TODO: memset_s(buffer, 0, streamSize ??

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

				int index = 0;
				this->global = new SubStream;
				Sheet* currentSheet = nullptr;

				while (index + 4 < streamSize)
				{
					unsigned short recordType = common::ReadUShort(buffer, streamSize, index);
					index += 2;
					unsigned short recordSize = common::ReadUShort(buffer, streamSize, index);
					index += 2;

					std::vector<uint8_t> data;
					if (index + recordSize < streamSize) {
						data.insert(data.end(), &buffer[index], &buffer[index + recordSize]);
					}
					Record* r = ParseRecord(recordType, data);
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
							index += streamSize; //exit, we're not decrypting, so we won't be able to parse the rest correctly
							break;
						default:
							break;
						}
						if (currentSheet != nullptr) {
							currentSheet->AddRecord(r);
						}
						else {
							this->global->AddRecord(r);
						}
					}
					else {
						//insert error parsing record type record??
					}
					index += recordSize;
				}

				delete buffer;

			}

			virtual std::string ToJson() const {
				std::ostringstream str;
				str << "{";
				str << this->buildBaseJson();
				if (this->global != nullptr) {
					str << ", \"globals\": { " << this->global->ToJson() << "}";
				}
				if (this->sheets.size() > 0) {
					str << ", \"sheets\": [";
					for (std::vector<Sheet>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {
						if (i != this->sheets.begin()) str << ",";
						str << (*i).ToJson();
					}
					str << "]";
				}
				str << "}";
				return str.str();
			}
			virtual std::string ToXml() const {
				std::ostringstream str;
				str << "<item>";
				str << this->buildBaseXml();
				if (this->global != nullptr) {
					str << "<globals>";
					str << this->global->ToXml();
					str << "</globals>";
				}
				if (this->sheets.size() > 0) {
					str << "<sheets>";
					for (std::vector<Sheet>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {
						str << (*i).ToXml();
					}
					str << "</sheets>";
				}
				str << "</item>";
				return str.str();
			}
		};
	}
}
