#pragma once

#include "Record.hpp"
#include "../structures/formulas/FormulaHeader.hpp"
#include "../structures/formulas/CellParsedFormula.hpp"
#include "../structures/formulas/Ptg.hpp"

namespace oless {
	namespace excel {
		namespace records {


			class FormulaRecord : public Record {
			private:
				excel::structures::formulas::FormulaHeader* header;
				excel::structures::formulas::CellParsedFormula* cpFormula;
				std::vector<excel::structures::formulas::Ptg*> children;
				std::string formula;

			public:
				FormulaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					auto buffer = this->Data.data();
					auto maxBuffer = this->Data.size();
					unsigned int index = 0;
					unsigned int bytesRead = 0;

					this->header = reinterpret_cast<excel::structures::formulas::FormulaHeader*>(buffer);
					index += 20;

					unsigned short max = common::ReadUShort(buffer, maxBuffer, index);
					index += 2;

					auto rgce = new excel::structures::formulas::Rgce();
					rgce->Parse(buffer, maxBuffer, index);
					this->children = rgce->list;
					index += rgce->bytesRead;

					std::ostringstream ss;
					for (std::vector<excel::structures::formulas::Ptg*>::const_iterator it = this->children.begin(); it != this->children.end(); it++) {
						if (it != this->children.begin()) { ss << ";"; }
						ss << (*it)->to_string();
					}

					this->formula = ss.str();
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";

					str << "<Cell>" << this->header->cell.to_string() << "</Cell>";
					str << "<Value>" << common::XmlEscape(this->header->val.Value()) << "</Value>";
					str << "<FormulaString>" << common::XmlEscape(this->formula) << "</FormulaString>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length << ",";
					str << "\"Cell\":\"" << this->header->cell.to_string() << "\",";
					str << "\"Value\":\"" << common::JsonEscape(this->header->val.Value()) << "\",";
					str << "\"FormulaString\":\"" << common::JsonEscape(this->formula) << "\"";

					str << "}";
					return str.str();
				}
			};
		}
	}
}