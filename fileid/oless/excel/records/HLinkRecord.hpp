#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-oshared/1a9f6231-df63-4a95-b998-5c2b95b82965
			// This structure specifies a string for a hyperlink.
			class HyperLinkString {
			public:
			};

			class HyperLinkMoniker {
			public:
			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-oshared/c0437222-4868-4660-81f8-6b7ee236d3f8
			// This structure specifies a hyperlink and hyperlink-related information.
			class HyperLinkObject {
			private:

			public:

			};


			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f0b9de34-b147-4f96-a1a3-ac21f6fd48fa
			// The HLink record specifies a hyperlink associated with a range of cells.
			class HLinkRecord : public Record {
			private:

			public:
				HLinkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
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