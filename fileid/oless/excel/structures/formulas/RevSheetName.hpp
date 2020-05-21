#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1713a39f-731d-4508-9e72-14da2b7dd8d3
				// ptg=
				// The RevSheetName structure specifies the sheet or workbook on which a defined name is defined, for a defined name that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
				class RevSheetName {
				public:
					XLUnicodeString sheet;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::exception("Not Implemented!");
					}
				};
			}
		}
	}
}
