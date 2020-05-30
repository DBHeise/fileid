#pragma once

#include "Record.hpp"
#include "../structures/LongRGB.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/affb9fe3-4721-495a-9e53-51c7d3c65480
			// The AreaFormat record specifies the patterns and colors used in a filled region of a chart (section 2.2.3.3). 
			class AreaFormatRecord : public Record {
			private:
				LongRGB rgbFore;
				LongRGB rgbBack;
				unsigned short fls;
				unsigned short A : 1;
				unsigned short B : 1;
				unsigned short reserved : 14;				
				unsigned short ivcFore;
				unsigned short ivcBack;

			public:
				AreaFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->rgbFore.Parse(buffer, max, index);
					index += this->rgbFore.bytesRead;

					this->rgbBack.Parse(buffer, max, index);
					index += this->rgbBack.bytesRead;

					this->fls = common::ReadUShort(buffer, max, index, true);
					index += 2;

					this->A = common::ExtractBits(buffer[index], 1, 1);
					this->B = common::ExtractBits(buffer[index], 1, 2);

					this->reserved = common::ReadUShort(buffer, max, index) << 2 >> 2;
					index += 2;

					this->ivcFore = common::ReadUShort(buffer, max, index, true);
					index += 2;

					this->ivcBack = common::ReadUShort(buffer, max, index, true);
					index += 2;

				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<rgbFore>" << this->rgbFore.ToXml() << "</rgbFore>";
					str << "<rgbBack>" << this->rgbBack.ToXml() << "</rgbBack>";
					str << "<fls>" << this->fls << "</fls>";
					str << "<A>" << this->A << "</A>";
					str << "<B>" << this->B << "</B>";
					str << "<reserved>" << this->reserved << "</reserved>";
					str << "<ivcFore>" << this->ivcFore << "</ivcFore>";
					str << "<ivcBack>" << this->ivcBack << "</ivcBack>";
					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"rgbFore\":" << this->rgbFore.ToJson();
					str << ",\"rgbBack\":" << this->rgbBack.ToJson();
					str << ",\"fls\":" << this->fls;
					str << ",\"A\":" << this->A;
					str << ",\"B\":" << this->B;
					str << ",\"reserved\":" << this->reserved;
					str << ",\"ivcFore\":" << this->ivcFore;
					str << ",\"ivcBack\":" << this->ivcBack;
					str << "}";
					return str.str();
				}


			};
		}
	}
}
