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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9104e80e-4fce-449f-8658-ae41ba5d3336
				// ptg=
				// The RevNameTabid structure specifies a non-external defined name that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
				class RevNameTabid {
				public:
					unsigned short tabid;
					RevLblName name;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						throw std::exception("Not Implemented!");
					}
				};
			}
		}
	}
}
