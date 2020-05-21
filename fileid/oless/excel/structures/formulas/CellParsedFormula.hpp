#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"
#include "ParsedFormulaBase.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7dd67f0a-671d-4905-b87b-4cc07295e442
				// The CellParsedFormula structure specifies a formula (section 2.2.2) stored in a cell.
				class CellParsedFormula : public ParsedFormulaBase {
				};
			}
		}
	}
}