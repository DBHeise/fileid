#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "ParsedFormulaBase.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f30fbda8-d382-4d5a-901f-4691743f83e2
				// The DVParsedFormula structure specifies a formula (section 2.2.2) used in a data validation rule.
				class DVParsedFormula : public ParsedFormulaBase {
				private:
					unsigned short unused;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->cce = common::ReadUShort(buffer, max, index, true);
						index += 2;

						this->unused = common::ReadUShort(buffer, max, index, true);
						index += 2;

						this->rgce.Parse(buffer, max, index);
						index += this->rgce.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}