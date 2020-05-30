#pragma once

#include "Record.hpp"
#include "../structures/XLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/3b945c1f-208a-481e-91cc-333111fce594
			// The FnGroupName record specifies a user-defined function category in the current workbook.
			class FnGroupNameRecord : public Record {
			private:
				std::string name;
			public:
				FnGroupNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

					auto s = excel::structures::XLUnicodeString::Read(data.data(), 0, data.size());
					this->name = s.string;
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Name>" << this->name << "</Name>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Name\":\"" << this->name << "\"";
					str << "}";
					return str.str();
				}

			};
		}
	}
}
