#pragma once
#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "SerAr.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/edd64b46-0fa0-4ef0-b95b-fe2cd41c7f73
				// The PtgExtraArray structure specifies the values for the corresponding PtgArray as specified in RgbExtra. 
				struct PtgExtraArray {
					unsigned char cols;
					unsigned char rows;
					SerAr a[0];
				};
			}
		}
	}
}