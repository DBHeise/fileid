#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/556ac2fe-a736-4f52-97dd-0cf98965252e
				// ptg=
				// The RevItab structure specifies a sheet of a workbook referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
				class RevItab {
				public:
					unsigned char type;
					unsigned short tabid;
					XLUnicodeString sheet;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::runtime_error("Not Implemented!");
					}

				};
			}
		}
	}
}