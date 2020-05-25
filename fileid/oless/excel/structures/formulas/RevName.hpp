#pragma once
#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RevNameTabid.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9ef68cc7-45d3-48a1-befd-2882c592e641
				// ptg=
				// The RevName structure specifies a defined name referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
				class RevName {
				public:
					unsigned short book;
					XLUnicodeString path;
					unsigned char fExtern;
					RevNameTabid name;
					RevNamePly externName;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::exception("Not Implemented!");
					}

				};
			}
		}
	}
}