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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/52863fc5-3d3c-4874-90e6-a7961902849f
				// ptg=0x05
				// The PtgMul structure specifies a binary-value-operator that multiplies the first and second expressions in a binary-value-expression.
				class PtgMul : public PtgBasic {
				private:
					
				public:
					PtgMul(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgMul";
					}
				};
			}
        }
    }
}
