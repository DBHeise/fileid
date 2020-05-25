#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RevItab.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/537671c1-12a2-49f0-96ea-8760fdc411ef
				// ptg=
				// The RevExtern structure specifies a range of sheets on a workbook that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
				class RevExtern {
				public:
					unsigned short book;
					XLUnicodeString path;
					RevItab itabFirst;
					RevItab itabLast;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::runtime_error("Not Implemented!");
					}

				};

			}
		}
	}
}