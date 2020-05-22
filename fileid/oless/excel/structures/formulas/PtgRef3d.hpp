#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceLoc.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1ca817be-8df3-4b80-8d35-46b5eb753577
				// ptg=0x3A or 0x5A or 0x7A
				// The PtgRef3d operand specifies a reference to a single cell on one or more sheets.
				class PtgRef3d : public PtgSubType_ixti {
				private:
					PtgRef3d(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType_ixti::Parse(buffer, max, offset); }
					RgceLoc loc;
				public:
					static PtgRef3d* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgRef3d* ans = new PtgRef3d(buffer, max, index);
						index += ans->bytesRead;

						ans->loc.Parse(buffer, max, index);
						index += ans->loc.bytesRead;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgRef3d(" << this->loc.to_string() << ")";
						return ss.str();
					}
				};
			}
        }
    }
}
