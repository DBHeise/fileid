#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e85d171a-9138-44bb-8e53-9cef48abbc0e
			// The HLink record specifies a hyperlink associated with a range of cells.
			struct HLinkTooltip {


			};

			class HLinkTooltipRecord : public Record {
			public:
				HLinkTooltipRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					
				}
				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";


					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length;

					str << "}";
					return str.str();
				}
			};
		}
	}
}