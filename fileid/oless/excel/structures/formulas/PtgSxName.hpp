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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/aa0ebf5c-29d2-4ec5-8639-46f844e7647d
				// ptg=0x18
				// The PtgSxName structure specifies a reference to a calculated field or a calculated item found in a PivotParsedFormula. The Rgce that contains this Ptg MUST be part of the formula field of an SxFmla record.
				class PtgSxName : public PtgBasic_elf {
				private:
					PtgSxName(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic_elf::Parse(buffer, max, offset); }
					unsigned int sxIndex;
				public:
					static PtgSxName* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgSxName* ans = new PtgSxName(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgSxName";
					}
				};
			}
        }
    }
}
