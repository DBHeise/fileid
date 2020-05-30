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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/c5cd4a9a-dfc1-4dfc-b06f-94d31c7e116c
				class ChartParsedFormula : public ParsedFormulaBase {
				};
			}
		}
	}
}
