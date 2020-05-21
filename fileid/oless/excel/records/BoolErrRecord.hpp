#pragma once

#include "Record.hpp"
#include "../structures/Cell.hpp"
#include "../structures/formulas/BErr.hpp"

namespace oless {
	namespace excel {
		namespace records {
			using namespace excel::structures;
			using namespace excel::structures::formulas;

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/eb6cc285-5663-4859-982b-6662ee116614
			// The BoolErr record specifies a cell that contains either a Boolean value or an error value.
			class BoolErrRecord : public Record {
				Cell* cell;
				unsigned short bBoolErr;
				unsigned short fError;

			public:
				BoolErrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->cell = reinterpret_cast<Cell*>(buffer);
					index += 6;

					this->bBoolErr = buffer[index];
					index++;

					this->fError = buffer[index];
					index++;
				}
				
				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<Cell>" << this->cell->to_string() << "</Cell>";
					str << "<fError>" << this->fError << "</fError>";
					str << "<bBoolErr>" << this->bBoolErr << "</bBoolErr>";
					if (this->fError == 0x0) {
						str << "<Value>" << std::boolalpha << this->bBoolErr;
						str << "</Value>";
					} else {
						str << "<Value>" << ErrorValueString((BErr)this->bBoolErr) << "</Value>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"Cell\":\"" << this->cell->to_string() << "\"";
					str << ",\"fError\":" << this->fError;
					str << ",\"bBoolErr\":" << this->bBoolErr;
					if (this->fError == 0x0) {
						str << ",\"Value\":\"" << std::boolalpha << this->bBoolErr;
						str << "\"";
					}
					else {
						str << ",\"Value\":\"" << ErrorValueString((BErr)this->bBoolErr) << "\"";
					}
					str << "}";
					return str.str();
				}
			};
		}
	}
}
