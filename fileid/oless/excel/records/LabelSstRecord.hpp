#pragma once

#include "Record.hpp"
#include "SSTRecord.hpp"
#include "../structures/Cell.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see:https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/3f52609d-816f-44a7-aad1-e0fe2abccebd
			// The LabelSst record specifies a cell that contains a string.
			class LabelSstRecord : public Record {
			private: 
				oless::excel::structures::Cell* cell;
				unsigned int isst;

				bool hasValue = false;
				std::string value;
			public:
				LabelSstRecord(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->cell = reinterpret_cast<oless::excel::structures::Cell*>(buffer);
					index += 6;

					this->isst = common::ReadUInt(buffer, max, index, true);
					
					//Lookup SST value
					auto r = p->GetPrevRecordOfType(0x00FC);
					if (r != nullptr) {
						if (SSTRecord* sst = dynamic_cast<SSTRecord*>(r)) {
							if (this->isst < sst->strings.size()) {
								this->hasValue = true;
								value = sst->strings[this->isst];
							}
						}
					}
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Cell>" << this->cell->to_string() << "</Cell>";
					str << "<isst>" << this->isst << "</isst>";
					if (this->hasValue) {
						str << "<Value>" << this->value << "</Value>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Cell\":\"" << this->cell->to_string() << "\"";
					str << ",\"isst\":" << this->isst;
					if (this->hasValue) {
						str << ",\"Value\":\"" << common::JsonEscape(this->value) << "\"";
					}
					str << "}";
					return str.str();
				}
			};
		}
	}
}
