#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/28de4981-1352-4a5e-a3b7-f15a8a6ce7fb
				// ptg=0x09
				// The PtgLt structure specifies a binary-value-operator that compares whether the first expression in a binary-value-expression is less than the second.
				class PtgLt : public PtgBasic {
				private:
				public:
					PtgLt(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() {this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgLt";
					}
				};
			}
		}
	}
}