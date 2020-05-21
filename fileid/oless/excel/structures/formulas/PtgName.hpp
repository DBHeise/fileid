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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5f05c166-dfe3-4bbf-85aa-31c09c0258c0
				// ptg=0x23 or 0x43 or 0x63
				// The PtgName operand specifies a reference to a defined name in the same workbook as the containing Rgce.
				class PtgName : public PtgSubType {
				private:
					PtgName(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned int nameindex;
				public:
					static PtgName* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgName* ans = new PtgName(buffer, max, offset);
						ans->nameindex = common::ReadUInt(buffer, max, offset + 1, true);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 4; }
					std::string to_string() const override {
						return "PtgName";
					}
				};
			}
        }
    }
}
