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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/dc352cde-62fc-4c68-99fd-186d6bc4d610
				// ptg=0x18
				// The PtgElfRadical natural language formula operand specifies a reference class reference to a range that is represented by a single-cell natural language label. The range is specified by PtgArea or PtgAreaErr that follows this PtgElfRadical in the formula (section 2.2.2). If this structure is followed in the formula by PtgArea, then one but not both of the following MUST be true:
				class PtgElfRadical : public PtgBasic_elf {
				private:
					PtgElfRadical(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic_elf::Parse(buffer, max, offset); }
				public:
					static PtgElfRadical* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgElfRadical* ans = new PtgElfRadical(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgElfRadical";
					}
				};
			}
		}
	}
}