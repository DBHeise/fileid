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

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fa735454-09d8-4982-a5fb-dabaa9f02d5d
				// The SerNil structure specifies a null value in an array of values.
				class SerNil : public SerAr {
				public:
					unsigned char reserved1; //0x0
					unsigned int unused1;
					unsigned int unused2;
				};
			}
		}
	}
}
