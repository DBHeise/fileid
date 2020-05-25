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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/304191e6-2c82-4542-8477-a1ffd548442e
				// ptg=0x18
				// The PtgElfRadicalLel natural language formula operand specifies a reference class reference to a range which is represented by a single-cell natural language label or a multiple-cell natural language label that has been deleted.
				class PtgElfRadicalLel : public PtgBasic_elf {
				private:
					PtgElfRadicalLel(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic_elf::Parse(buffer, max, offset); }
					unsigned short ilel;
					unsigned char fQuoted : 1;
				public:
					static PtgElfRadicalLel* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgElfRadicalLel* ans = new PtgElfRadicalLel(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgElfRadicalLel";
					}
				};
			}
        }
    }
}
