#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/0e49033d-5dc7-40f1-8fca-eb3b8b1c2c91
				// ptg=0x0E
				// The PtgNe structure specifies a binary-value-operator that compares whether the second expression in a binary-value-expression is not equal to the first.
				class PtgNe : public PtgBasic {
				private:
					
				public:
					PtgNe(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset); 
					}

					std::string to_string() const override {
						return "PtgNe";
					}
				};
			}
        }
    }
}
