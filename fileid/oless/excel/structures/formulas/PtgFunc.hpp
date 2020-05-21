#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "helper.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {
				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/87ce512d-273a-4da0-a9f8-26cf1d93508d
				// ptg=0x21 or 0x41 or 0x61
				// The PtgFunc structure specifies a call to a function with a fixed number of parameters, as defined in function-call.
				class PtgFunc : public PtgSubType {
				private:
					PtgFunc(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned short iftab;
				public:
					static PtgFunc* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgFunc* ans = new PtgFunc(buffer, max, offset);
						ans->iftab = common::ReadUShort(buffer, max, offset + 1);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 2; }
					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgFunc(" << GetFunctionName_FTab(this->iftab) << ")";
						return ss.str();
					}
				};
			}
		}
	}
}