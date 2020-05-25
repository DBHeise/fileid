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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/ee15a1fa-77bb-45e1-8c8c-0e7bef7f7552
				// ptg=0x04
				// The PtgSub structure specifies a binary-value operator that subtracts the second expression in a binary-value-expression from the first.
				class PtgSub : public PtgBasic {
				private:
					
				public:
					PtgSub(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgSub";
					}
				};
			}
        }
    }
}
