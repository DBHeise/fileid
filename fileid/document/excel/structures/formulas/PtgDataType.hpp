#pragma once
#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/80d504ba-eb5d-4a0f-a5da-3dcc792dd78e
				// The PtgDataType enumeration specifies the data type of a Ptg.
				enum class PtgDataType : unsigned char {
					REFERENCE = 0x1,
					VALUE = 0x2,
					ARRAY = 0x3
				};
			}
		}
	}
}