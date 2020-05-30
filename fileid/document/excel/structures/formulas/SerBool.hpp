#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8c22e17f-0f97-4597-b2bd-7a2f5ddfc72d
				// The SerBool structure specifies a Boolean (section 2.5.14) value in an array of values.
				class SerBool : public SerAr {
				public:
					unsigned char reserved1; //0x4
					unsigned char f;
					unsigned char reserved2;
					unsigned short unused1;
					unsigned int unused2;
				};
			}
		}
	}
}