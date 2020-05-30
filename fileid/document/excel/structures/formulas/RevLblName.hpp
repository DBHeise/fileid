#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/14b8e004-e116-451b-bf84-e26e963aa4a4
				// ptg=
				// The RevLblName structure specifies the name of a defined name that is referenced by a formula in a revision as specified in the Formulas overview (section 2.2.2).
				class RevLblName {
				public:
					unsigned char iBuiltin;
					XLNameUnicodeString st;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::runtime_error("Not Implemented!");
					}

				};
			}
		}
	}
}