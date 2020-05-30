#pragma once

#include "../../../../common.hpp"

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
				class ArrayParsedFormula : public ParsedFormulaWithExtraBase { };
			}
		}
	}
}