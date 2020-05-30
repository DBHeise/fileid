#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/054d699a-4383-4bbf-9df2-6a4020119c1e
				// ptg=0x08
				// The PtgConcat structure specifies a binary-value-operator that appends the second expression in binary-value-expression to the first.
				class PtgConcat : public PtgBasic {
				private:
					
				public:
					PtgConcat(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					
					std::string to_string() const override {
						return "PtgConcat";
					}
				};
			}
		}
	}
}