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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f9eba5de-1ff6-4d52-9753-f9c1e446c774
				// ptg=0x39 or 0x59 or 0x79
				// The PtgNameX structure specifies a reference to a defined name in an external workbook.
				class PtgNameX : public PtgSubType_ixti {
				private:
					PtgNameX(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType_ixti::Parse(buffer, max, offset); }
					unsigned int nameindex;
				public:
					static PtgNameX* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgNameX* ans = new PtgNameX(buffer, max, offset);
						ans->nameindex = common::ReadUInt(buffer, max, offset + 3, true);
						return ans;
					}
					unsigned int size() const override { return PtgSubType_ixti::size() + 4; }
					std::string to_string() const override {
						return "PtgNameX";
					}
				};
			}
        }
    }
}
