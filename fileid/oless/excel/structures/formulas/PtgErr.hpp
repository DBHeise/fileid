#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "BErr.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/4746c46e-8301-4d72-aaa8-742f5404b5db
				// ptg=0x1C
				// The PtgErr operand specifies an error code.
				class PtgErr : public PtgBasic {
				private:
					PtgErr(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					BErr err;
				public:
					static PtgErr* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgErr* ans = new PtgErr(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 1; }
					std::string to_string() const override {
						return "PtgErr";
					}
				};
			}
		}
	}
}