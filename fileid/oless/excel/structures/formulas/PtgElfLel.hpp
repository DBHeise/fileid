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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/67784d96-e87d-4f97-b643-f8f2176a6148
				// ptg=0x18
				// The PtgElfLel natural language formula operand specifies a reference to a range which is represented by a single-cell natural language label or a multiple-cell natural language label that has been deleted.?
				class PtgElfLel : public PtgBasic_elf {
				private:
					PtgElfLel(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic_elf::Parse(buffer, max, offset); }
					unsigned short ilel;
					unsigned char fQuoted : 1;
				public:
					static PtgElfLel* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgElfLel* ans = new PtgElfLel(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgElfLel";
					}
				};
			}
        }
    }
}
