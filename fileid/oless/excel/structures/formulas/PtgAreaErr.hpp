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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/bbc29b52-b581-4417-b18c-a4ac430a8dc0
				// ptg=0x2B or 0x4B or 0x6B
				// The PtgAreaErr operand specifies an invalid reference to a cell range.
				class PtgAreaErr : public PtgSubType {
				private:
					PtgAreaErr(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned short unused1;
					unsigned short unused2;
					unsigned short unused3;
					unsigned short unused4;
				public:
					static PtgAreaErr* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgAreaErr* ans = new PtgAreaErr(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 8; }
					std::string to_string() const override {
						return "PtgAreaErr";
					}
				};
			}
		}
	}
}