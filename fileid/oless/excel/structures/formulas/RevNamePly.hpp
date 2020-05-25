#pragma once
#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RevLblName.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fbe58e96-929f-4c7f-9d3b-f5ad8f08dd36
				// ptg=
				// The RevNamePly structure specifies a defined name in an external workbook that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2), and the sheet on which it is defined.
				class RevNamePly {
				public:
					RevSheetName sheet;
					RevLblName name;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::runtime_error("Not Implemented!");
					}
				};
			}
		}
	}
}
