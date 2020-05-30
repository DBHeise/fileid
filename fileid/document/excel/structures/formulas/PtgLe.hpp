#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/92c13f4d-89d3-45a9-a395-4643e5b27b1d
				// ptg=0x0A
				// The PtgLe structure specifies a binary-value-operator that compares whether the first expression in a binary-value-expression is less than or equal to the second.
				class PtgLe : public PtgBasic {
				private:
					
				public:
					PtgLe(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgLe";
					}
				};
			}
		}
	}
}