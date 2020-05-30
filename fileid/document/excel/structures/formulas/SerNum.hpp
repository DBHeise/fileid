#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7a876271-cde6-4b80-a35e-ceddf65aedba
				// The SerNum structure specifies a numeric value in an array of values.
				class SerNum : public SerAr {
				public:
					unsigned char reserved1; //0x1
					double xnum;
				};

			}
		}
	}
}
