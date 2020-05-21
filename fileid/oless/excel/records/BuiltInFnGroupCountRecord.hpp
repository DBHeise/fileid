#pragma once
#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/970af5a7-a51d-4a62-9255-01456033ebd6
			// The BuiltInFnGroupCount record specifies the beginning of a collection of records as defined by the Globals Substream ABNF.The collection of records specifies information about the built - in function categories in the workbook.
			class BuiltInFnGroupCountRecord : public Record {
			private:
				unsigned short count;
			public:
				BuiltInFnGroupCountRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					unsigned int index = 0;
					auto buffer = this->Data.data();
					auto max = this->Data.size();

					this->count = common::ReadUShort(buffer, max, index);


				}
				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Count>" << this->count << "</Count>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Count\":" << this->count;
					str << "}";
					return str.str();
				}
			};
		}
	}
}
