#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceArea.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/869033ad-6304-4b9a-b2ba-1e7794ae345a
				// ptg=0x3B or 0x5B or 0x7B
				// The PtgArea3d operand specifies a reference to the same rectangular range of cells on one or more sheets. If the formula (section 2.2.2) containing this structure is part of a revision as specified in the Formulas overview, then there MUST be a RevExtern in the RgbExtra corresponding to this PtgArea3d, which specifies those sheets.
				class PtgArea3d : public PtgSubType_ixti {
				private:
					PtgArea3d(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType_ixti::Parse(buffer, max, offset); }
					RgceArea area;
				public:
					static PtgArea3d* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgArea3d* ans = new PtgArea3d(buffer, max, offset);
						ans->area.Parse(buffer, max, offset + 3);
						ans->bytesRead += ans->area.bytesRead;
						return ans;
					}
					
					std::string to_string() const override {
						return "PtgArea3d(" + this->area.to_string() + ")";
					}
				};
			}
		}
	}
}