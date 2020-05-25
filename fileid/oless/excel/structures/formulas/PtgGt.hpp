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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/08104e30-5fb6-467a-87ed-978eb456366c
				// ptg=0x0D
				// The PtgGt structure specifies a binary-value-operator that compares whether the first expression in a binary-value-expression is greater than the second.
				class PtgGt : public PtgBasic {
				private:
					
				public:
					PtgGt(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgGt";
					}
				};
			}
		}
	}
}
