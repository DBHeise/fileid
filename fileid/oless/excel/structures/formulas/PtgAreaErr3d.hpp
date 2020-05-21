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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e91dfca4-7b5e-4e44-86a5-e6621222a3a2
				// ptg=0x3D or  0x5D or  0x7D
				// The PtgAreaErr3d operand specifies an invalid reference to the same rectangular range of cells on one or more sheets. If the formula (section 2.2.2) containing this structure is part of a revision as specified in the Formulas overview, then there MUST be a RevExtern in the RgbExtra corresponding to this PtgAreaErr3d, which specifies those sheets.
				class PtgAreaErr3d : public PtgSubType_ixti {
				private:
					PtgAreaErr3d(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType_ixti::Parse(buffer, max, offset); }
					unsigned short unused1;
					unsigned short unused2;
					unsigned short unused3;
					unsigned short unused4;
				public:
					static PtgAreaErr3d* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgAreaErr3d* ans = new PtgAreaErr3d(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType_ixti::size() + 8; }
					std::string to_string() const override {
						return "PtgAreaErr3d";
					}
				};
			}
		}
	}
}