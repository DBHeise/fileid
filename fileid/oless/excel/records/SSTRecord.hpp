#pragma once

#include "Record.hpp"
#include "../structures/XLUnicodeRichExtendedString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SSTRecord : public Record {
			private:
				int cstTotal;
				int cstUnique;				
			public:
				std::vector<std::string> strings;
				SSTRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) 
				{
					unsigned int index = 0;
					auto buffer = this->Data.data();
					auto max = this->Data.size();

					this->cstTotal = common::ReadSInt(buffer, max, index, true);
					index += 4;
					this->cstUnique = common::ReadSInt(buffer, max, index, true);
					index += 4;

					for (unsigned int i = 0; i < this->cstUnique; i++) {
						auto s = oless::excel::structures::XLUnicodeRichExtendedString::Read(buffer, index, max);
						index += s.bytesRead;
						this->strings.push_back(s.String());
					}					
				}
				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<cstTotal>" << this->cstTotal << "</cstTotal>";
					str << "<cstUnique>" << this->cstUnique << "</cstUnique>";
					if (this->strings.size() > 0) {
						str << "<strings>";
						for (auto it = this->strings.begin(); it != this->strings.end(); it++) {
							str << "<string>" << (*it) << "</string>";
						}
						str << "</strings>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"cstTotal\":" << this->cstTotal;
					str << ",\"cstUnique\":" << this->cstUnique;
					if (this->strings.size() > 0) {
						str << ",\"strings\":[";
						for (auto it = this->strings.begin(); it != this->strings.end(); it++) {
							if (it != this->strings.begin()) { str << ","; }
							str << "\"" << common::JsonEscape(*it) << "\"";
						}
						str << "]";
					}
					str << "}";
					return str.str();
				}

			};
		}
	}
}
