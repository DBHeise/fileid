#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			struct RKNumber {
				unsigned int fX100 : 1;
				unsigned int fInt : 1;
				unsigned int num : 30;
				std::string GetValue() {
					std::ostringstream str;
					if (this->fInt == 0x1) {
						if (this->fX100 == 0x0) {
							str << this->num;
						} else if (this->fX100 == 0x1) {
							str << this->num / 100;
						}						
					} else {
						unsigned int n1 = this->num;
						float* n2 = reinterpret_cast<float*>(&n1);
						str << *n2;
					}
					return str.str();
				}
			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/656e0e79-8b9d-4854-803f-23ec62080678
			// The RK record specifies the numeric data contained in a single cell.
			class RKRecord : public Record {
				unsigned short rw;
				unsigned short col;
				unsigned short ixfe;
				RKNumber* number;
			public:
				RKRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->rw = common::ReadUShort(buffer, max, index);
					index += 2;

					this->col = common::ReadUShort(buffer, max, index);
					index += 2;

					this->ixfe = common::ReadUShort(buffer, max, index);
					index += 2;

					this->number = reinterpret_cast<RKNumber*>(buffer + index);
					index += 4;
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<rw>" << this->rw << "</rw>";
					str << "<col>" << this->col << "</col>";
					str << "<ixfe>" << this->ixfe << "</ixfe>";
					str << "<fX100>" << this->number->fX100 << "</fX100>";
					str << "<fInt>" << this->number->fInt << "</fInt>";
					str << "<num>" << this->number->num << "</num>";
					str << "<Cell>" << ColNumToName(this->col) << this->rw + 1 << "</Cell>";
					str << "<Value>" << this->number->GetValue() << "</Value>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"rw\":" << this->rw;
					str << ",\"col\":" << this->col;
					str << ",\"ixfe\":" << this->ixfe;
					str << ",\"fX100\":" << this->number->fX100;
					str << ",\"fInt\":" << this->number->fInt;
					str << ",\"num\":" << this->number->num;
					str << ",\"Cell\":\"" << ColNumToName(this->col) << this->rw + 1 << "\"";
					str << ",\"Value\":" << this->number->GetValue();
					str << "}";
					return str.str();
				}
			};
		}
	}
}
