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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/acaed966-4eee-4578-ae5b-a23a781a8944
				class CFVOParsedFormula : public ParsedFormulaBase {
				};
			}
		}
	}
}