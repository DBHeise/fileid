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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/307f13db-e5d2-4b35-8309-d5452908a2d4
				// ptg=0x3C or 0x5C or 0x7C
				// The PtgRefErr3d operand specifies an invalid reference to a cell on one or more sheets. If the formula (section 2.2.2) containing this structure is part of a revision as specified in the Formulas overview (section 2.2.2), then there MUST be a RevExtern in the RgbExtra corresponding to this PtgRefErr3d, which specifies those sheets.
				class PtgRefErr3d : public PtgSubType_ixti {
				private:
					PtgRefErr3d(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType_ixti::Parse(buffer, max, offset); }
					unsigned short unused1;
					unsigned short unused2;
				public:
					static PtgRefErr3d* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgRefErr3d* ans = new PtgRefErr3d(buffer, max, index);
						index += ans->bytesRead;

						ans->unused1 = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->unused2 = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgRefErr3d";
					}
				};
			}
        }
    }
}
