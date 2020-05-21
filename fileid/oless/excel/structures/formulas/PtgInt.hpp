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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/508ecf18-3b81-4628-95b3-7a9d2a295bca
				// ptg=0x1E
				// The PtgInt operand specifies an unsigned integer value.
				class PtgInt : public PtgBasic {
				private:
					PtgInt(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned short integer;
				public:
					static PtgInt* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgInt* ans = new PtgInt(buffer, max, offset);
						ans->integer = common::ReadUShort(buffer, max, offset + 1);
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 2; }
					std::string to_string() const override {
						return "PtgInt(" + std::to_string(this->integer) + ")";
					}
				};
			}
		}
	}
}
