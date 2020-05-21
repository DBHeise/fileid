#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "ParsedFormulaBase.hpp"
#include "RgbExtra.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/242bcf20-047b-43aa-ad58-9a7288545cbc
				// The ArrayParsedFormula structure specifies an array formula(section 2.2.2).
				class ArrayParsedFormula : public ParsedFormulaBase {
				private:
					RgbExtra rgcb;

				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						ParsedFormulaBase::Parse(buffer, max, offset);
						
						unsigned int index = offset + this->bytesRead;

						this->rgcb.Parse(buffer, max, index);
						index += this->rgcb.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}