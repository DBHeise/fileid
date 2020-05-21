#pragma once

#include "Record.hpp"
#include "../structures/XLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

	
			class CodeNameRecord : public Record {
			private:
				std::string name;
			public:
				CodeNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					this->name = excel::structures::XLUnicodeString::Read(this->Data.data(), 0, this->Data.size()).string;
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";

					str << "<CodeName>" << this->name << "</CodeName>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length << ",";
					str << "\"CodeName\":\"" << this->name << "\"";

					str << "}";
					return str.str();
				}
			};
		}
	}
}