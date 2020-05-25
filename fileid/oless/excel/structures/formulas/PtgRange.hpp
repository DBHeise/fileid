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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f5ef334a-bc47-41ce-ba5d-096373423fab
				// ptg=0x11
				// The PtgRange structure specifies the range operation, where the minimum bounding rectangle of the first expression and the second expression is generated.
				class PtgRange : public PtgBasic {
				private:
					PtgRange(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
				public:
					static PtgRange* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgRange* ans = new PtgRange(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgRange";
					}
				};
			}
        }
    }
}
