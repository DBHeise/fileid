#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../Cell.hpp"
#include "../FormulaValue.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {
				
				struct undoc_cache {
					unsigned short rw;
					unsigned short col : 8;
					unsigned short fIamNotTop : 1;
					unsigned short fNotNull : 1;
					unsigned short fEnt : 1;
					unsigned short itab : 5;
				};

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8e3c6978-6c9f-4915-a826-07613204b244
				// The Formula record specifies a formula (section 2.2.2) for a cell.
				struct FormulaHeader {
					Cell cell;
					FormulaValue val;
					unsigned short fAlwaysCalc : 1;
					unsigned short fCaclOnLoad : 1; //reserved1
					unsigned short fFill : 1;
					unsigned short fShrFmla : 1;
					unsigned short fNeedBuild : 1;	//reserved2
					unsigned short fClearErrors : 1;
					unsigned short reserved3 : 10;	//unused?
					undoc_cache chn;
				};

			}
		}
	}
}