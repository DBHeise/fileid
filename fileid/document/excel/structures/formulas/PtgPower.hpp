#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e115b216-5dda-4a5b-95d2-cadf0ada9a82
				// ptg=0x07
				// The PtgPower structure specifies a binary-value-operator that raises the first expression in a binary-value-expression to the power of the second.
				class PtgPower : public PtgBasic {
				private:
					
				public:
					PtgPower(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgPower";
					}
				};
			}
        }
    }
}
