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
					
					this->formula = rgce->ToFormulaString();
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();

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
					str << this->getBaseJson();
					str << ",\"Cell\":\"" << this->header->cell.to_string() << "\",";
					str << "\"Value\":\"" << common::JsonEscape(this->header->val.Value()) << "\",";
					str << "\"FormulaString\":\"" << common::JsonEscape(this->formula) << "\"";

					str << "}";
					return str.str();
				}
			};
		}
	}
}