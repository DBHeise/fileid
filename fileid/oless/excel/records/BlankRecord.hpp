#pragma once

#include "Record.hpp"
#include "../structures/Cell.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/2918f1db-545e-432a-8f57-599c44251f07
			// The Blank record specifies an empty cell with no formula or value.
			class BlankRecord : public Record {
				excel::structures::Cell* cell;

			public:
				BlankRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->cell = reinterpret_cast<excel::structures::Cell*>(buffer);
					index += 6;
				}
				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Cell>" << this->cell->to_string() << "</Cell>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Cell\":\"" << this->cell->to_string() << "\"";
					str << "}";
					return str.str();
				}

			};
		}
	}
}
