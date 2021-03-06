#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d197275e-cb7f-455c-b9b5-7e968412d470
				// ptg=0x0B
				// The PtgEq structure specifies the comparison of whether the first expression is equal to the second expression.
				class PtgEq : public PtgBasic {
				private:
					
				public:
					PtgEq(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset); 
					}

					std::string to_string() const override {
						return "PtgEq";
					}
				};
			}
		}
	}
}