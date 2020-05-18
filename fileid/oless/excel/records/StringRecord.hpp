#pragma once

#include "Record.hpp"
#include "../MSExcel.strings.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class StringRecord : public Record {
			private:
				std::string record;
			public:
				StringRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{					
					this->record = Excel::XLUnicodeString::Read(this->Data.data(), 0, this->Data.size()).string;
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";

					str << "<String><![CDATA[" << this->record << "]]></String>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length << ",";
					str << "\"String\":\"" << common::JsonEscape(this->record) << "\"";

					str << "}";
					return str.str();
				}
			};
		}
	}
}