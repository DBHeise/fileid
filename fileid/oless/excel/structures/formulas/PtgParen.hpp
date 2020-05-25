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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7a5b73da-c552-4fa7-a4d0-1a36032a5622
				// ptg=0x15
				// The PtgParen display token specifies that parentheses are displayed around the expression in a display-precedence-expression.
				class PtgParen : public PtgBasic {
				private:
					
				public:
					PtgParen(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset); 
					}
					
					std::string to_string() const override {
						return "PtgParen";
					}
				};
			}
        }
    }
}
