#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceAreaRel.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f2c8529a-25b1-4c75-838b-a48ef6384f86
				// ptg=0x2D or 0x4D or 0x6D
				// The PtgAreaN operand specifies a reference to a rectangular range of cells as an RgceAreaRel.
				class PtgAreaN : public PtgSubType {
				private:
					PtgAreaN(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					RgceAreaRel area;
				public:
					static PtgAreaN* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgAreaN* ans = new PtgAreaN(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 8; }
					std::string to_string() const override {
						return "PtgAreaN";
					}
				};
			}
		}
	}
}