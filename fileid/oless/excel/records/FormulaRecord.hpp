#pragma once

#include "Record.hpp"
#include "../structures/Cell.hpp"
#include "../structures/FormulaValue.hpp"
#include "../structures/formulas/CellParsedFormula.hpp"
#include "../structures/formulas/Ptg.hpp"

namespace oless {
	namespace excel {
		namespace records {

			struct fakeFormulaRecordFlags {
				unsigned short fAlwaysCalc : 1;
				unsigned short fCaclOnLoad : 1; //reserved1
				unsigned short fFill : 1;
				unsigned short fShrFmla : 1;
				unsigned short fNeedBuild : 1;	//reserved2
				unsigned short fClearErrors : 1;
				unsigned short reserved3 : 10;	//unused?
				unsigned short rw;
				unsigned short col : 8;
				unsigned short fIamNotTop : 1;
				unsigned short fNotNull : 1;
				unsigned short fEnt : 1;
				unsigned short itab : 5;
			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8e3c6978-6c9f-4915-a826-07613204b244
			// The Formula record specifies a formula (section 2.2.2) for a cell.
			class FormulaRecord : public Record {
			private:
				excel::structures::Cell cell;
				excel::structures::FormulaValue val;
				fakeFormulaRecordFlags flags;
				excel::structures::formulas::CellParsedFormula* cpFormula;

				std::string formula;

			public:
				FormulaRecord(IRecordParser* parser, unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->cell.Parse(buffer, max, index);
					index += this->cell.bytesRead;

					this->val.Parse(buffer, max, index);
					index += this->val.bytesRead;

					auto flags = new fakeFormulaRecordFlags();
					flags = reinterpret_cast<fakeFormulaRecordFlags*>(buffer + index);
					this->flags = *flags;
					index += 6;

					this->cpFormula = new excel::structures::formulas::CellParsedFormula(parser);
					this->cpFormula->Parse(buffer, max, index);
					index += this->cpFormula->bytesRead;

					this->formula = this->cpFormula->ToFormulaString();
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<fAlwaysCalc>" << this->flags.fAlwaysCalc << "</fAlwaysCalc>";
					str << "<fCaclOnLoad>" << this->flags.fCaclOnLoad << "</fCaclOnLoad>";
					str << "<fFill>" << this->flags.fFill << "</fFill>";
					str << "<fShrFmla>" << this->flags.fShrFmla << "</fShrFmla>";
					str << "<fNeedBuild>" << this->flags.fNeedBuild << "</fNeedBuild>";
					str << "<fClearErrors>" << this->flags.fClearErrors << "</fClearErrors>";
					str << "<reserved3>" << this->flags.reserved3 << "</reserved3>";
					str << "<rw>" << this->flags.rw << "</rw>";
					str << "<col>" << this->flags.col << "</col>";
					str << "<fIamNotTop>" << this->flags.fIamNotTop << "</fIamNotTop>";
					str << "<fNotNull>" << this->flags.fNotNull << "</fNotNull>";
					str << "<fEnt>" << this->flags.fEnt << "</fEnt>";
					str << "<itab>" << this->flags.itab << "</itab>";
					str << "<Cell>" << this->cell.to_string() << "</Cell>";
					str << "<Value>" << common::XmlEscape(this->val.Value()) << "</Value>";
					str << "<FormulaString>" << common::XmlEscape(this->formula) << "</FormulaString>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"fAlwaysCalc\":" << this->flags.fAlwaysCalc;
					str << ",\"fCaclOnLoad\":" << this->flags.fCaclOnLoad;
					str << ",\"fFill\":" << this->flags.fFill;
					str << ",\"fShrFmla\":" << this->flags.fShrFmla;
					str << ",\"fNeedBuild\":" << this->flags.fNeedBuild;
					str << ",\"fClearErrors\":" << this->flags.fClearErrors;
					str << ",\"reserved3\":" << this->flags.reserved3;
					str << ",\"rw\":" << this->flags.rw;
					str << ",\"col\":" << this->flags.col;
					str << ",\"fIamNotTop\":" << this->flags.fIamNotTop;
					str << ",\"fNotNull\":" << this->flags.fNotNull;
					str << ",\"fEnt\":" << this->flags.fEnt;
					str << ",\"itab\":" << this->flags.itab;
					str << ",\"Cell\":\"" << this->cell.to_string() << "\"";
					str << ",\"Value\":\"" << common::JsonEscape(this->val.Value()) << "\"";
					str << ",\"FormulaString\":\"" << common::JsonEscape(this->formula) << "\"";

					str << "}";
					return str.str();
				}
			};
		}
	}
}