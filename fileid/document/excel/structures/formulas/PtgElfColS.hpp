#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/cc02acdf-f404-4318-9847-8d4cbf523966
				// ptg=0x18
				// The PtgElfColS natural language formula operand specifies a reference class reference to a range within a column that is identified by a multiple-cell natural language label. There MUST be a PtgExtraElf in the RgbExtra corresponding to this PtgElfColS. The correspondence between PtgElfColS and PtgExtraElf structures is specified in RgbExtra.
				class PtgElfColS : public PtgBasic_elf {
				private:

				public:
					PtgElfColS(unsigned char* buffer, size_t max, unsigned int offset) : PtgBasic_elf() {
						this->Parse(buffer, max, offset);
					}

					std::string to_string() const override {
						return "PtgElfColS";
					}
				};
			}
		}
	}
}