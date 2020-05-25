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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/0185f97f-c731-4852-bd0d-0eb0d8b3457f
				// ptg=0x0C
				// The PtgGe structure specifies a binary-value-operator that compares whether the first expression in a binary-value-expression is greater than or equal to the second.
				class PtgGe : public PtgBasic {
				private:
					PtgGe(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
				public:
					static PtgGe* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgGe* ans = new PtgGe(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgGe";
					}
				};
			}
		}
	}
}
