#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "ParsedFormulaBase.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/ef40c8e8-8ffe-4d72-811b-090f8123ba07
				// The CFParsedFormula structure specifies a formula (section 2.2.2) used in a conditional formatting rule.
				class CFParsedFormula : public ParsedFormulaBase {
				};
			}
		}
	}
}
