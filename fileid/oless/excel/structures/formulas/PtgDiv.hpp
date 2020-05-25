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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/10585b24-618d-47f4-8ffa-65811d18ad13
				// ptg=0x06
				// The PtgDiv structure specifies a binary-value-operator that divides the first expression in a binary-value-expression by the second.
				class PtgDiv : public PtgBasic {
				private:
					
				public:
					PtgDiv(unsigned char* buffer, size_t max, unsigned int offset) {
						this->Parse(buffer, max, offset);
					}
					
					std::string to_string() const override {
						return "PtgDiv";
					}
				};
			}
		}
	}
}