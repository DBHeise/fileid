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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/69352e6c-e712-48d7-92d1-0bf7c1f61f69
				// ptg=0x16
				// The PtgMissArg operand specifies a missing value.
				class PtgMissArg : public PtgBasic {
				private:
					
				public:
					PtgMissArg(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgMissArg";
					}
				};
			}
		}
	}
}