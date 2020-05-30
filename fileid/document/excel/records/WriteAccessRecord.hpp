#pragma once

#include "Record.hpp"
#include "../structures/XLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class WriteAccessRecord : public Record {
			public:
				std::string username;

				WriteAccessRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					auto u = oless::excel::structures::XLUnicodeString::Read(buffer, index, max);
					this->username = u.string;
				}
				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<username>" << this->username << "</username>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"username\":\"" << this->username << "\"";
					str << "}";
					return str.str();
				}

			};
		}
	}
}
