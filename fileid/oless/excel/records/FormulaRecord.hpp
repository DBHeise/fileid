#pragma once

#include "Record.hpp"
#include "..\MSExcel.formulas.hpp"
#include "..\MSExcel.ptg.hpp"


namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6cdf7d38-d08c-4e56-bd2f-6c82b8da752e
			// The Rgce structure specifies a set of Ptgs, laid out sequentially in the file.
			struct Rgce {

			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/70f743b2-a853-4c57-88be-8af637ac6e43
			// The RgbExtra structure specifies a set of structures, laid out sequentially in the file, that correspond to and MUST exist for certain Ptgs in the Rgce. 
			struct RgbExtra {

			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7dd67f0a-671d-4905-b87b-4cc07295e442
			// The CellParsedFormula structure specifies a formula (section 2.2.2) stored in a cell.
			struct CellParsedFormula {
				unsigned short cce;
				Rgce rgce;
				RgbExtra rgcb;
			};


			class FormulaRecord : public Record {
			private:
				FormulaHeader* header;
				CellParsedFormula* cpFormula;
				std::vector<Formulas::Ptg*> children;
				std::string formula;

			public:
				FormulaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					auto buffer = this->Data.data();
					unsigned int maxBuffer = this->Data.size();
					this->header = reinterpret_cast<FormulaHeader*>(buffer);
					unsigned int index = 20;
					unsigned int bytesRead = 0;
					unsigned short max = common::ReadUShort(buffer, maxBuffer, index);
					index += 2;

					this->children = Formulas::Parse(buffer, index, maxBuffer);

					std::ostringstream ss;
					for (std::vector<Formulas::Ptg*>::const_iterator it = this->children.begin(); it != this->children.end(); it++) {
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
					str << "<Value>" << this->header->val.Value() << "</Value>";
					str << "<FormulaString>" << this->formula << "</FormulaString>";

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