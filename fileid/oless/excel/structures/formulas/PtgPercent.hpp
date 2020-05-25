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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/980d459a-e1d2-48c3-b00b-662b029247ce
				// ptg=0x14
				// The PtgPercent structure specifies a unary-operator which divides the expression in a unary-expression by 100.
				class PtgPercent : public PtgBasic {
				private:
					
				public:
					PtgPercent(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset); 
					}

					std::string to_string() const override {
						return "PtgPercent";
					}
				};
			}
        }
    }
}
