#pragma once

#include "Record.hpp"
#include "../structures/ShortXLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/b9ec509a-235d-424e-871d-f8e721106501
			// The BoundSheet8 record specifies basic information about a sheet, including the sheet name, hidden state, and type of sheet.
			struct BoundSheetHeader {
				unsigned int lbPlyPos;
				unsigned short hsState : 2;
				unsigned short unused1 : 6;
				unsigned short dt : 8;
			};

			class BoundSheet8Record : public Record {
			private:
				BoundSheetHeader* header;
				

			public:
				std::string Name;

				BoundSheet8Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					auto buffer = this->Data.data();
					this->header = reinterpret_cast<BoundSheetHeader*>(buffer);
					this->Name = excel::structures::ShortXLUnicodeString::Read(buffer, 6).string;
				}

				BoundSheetHeader* GetRawHeader() {
					return this->header;
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Name>" << common::XmlEscape(this->Name) << "</Name>";
					str << "<State>" << this->header->hsState << "</State>";
					str << "<SheetType>" << this->header->dt << "</SheetType>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Name\":\"" << common::JsonEscape(this->Name) << "\",";
					str << "\"State\":" << this->header->hsState << ",";
					str << "\"SheetType\":" << this->header->dt;

					str << "}";
					return str.str();
				}
			};
		}
	}
}