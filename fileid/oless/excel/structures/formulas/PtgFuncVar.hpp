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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5d105171-6b73-4f40-a7cd-6bf2aae15e83
				// ptg=0x22 or 0x42 or 0x62
				// The PtgFuncVar structure specifies a call to a function with a variable number of parameters as defined in function-call.
				class PtgFuncVar : public PtgSubType {
				private:
					PtgFuncVar(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned char cparams;
					unsigned short tab : 15;
					unsigned char fCeFunc : 1;
				public:
					static PtgFuncVar* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgFuncVar* ans = new PtgFuncVar(buffer, max, offset);
						ans->cparams = buffer[offset + 1];
						ans->tab = common::ReadUShort(buffer, max, offset + 2) << 1 >> 1;
						ans->fCeFunc = common::ExtractBits(buffer[offset + 3], 1, 7);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 3; }
					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgFuncVar(";
						if (this->fCeFunc == 1) {
							ss << GetFunctionName_CeTab(this->tab);
						}
						else {
							ss << GetFunctionName_FTab(this->tab);
						}
						ss << ")";
						return ss.str();
					}
				};
			}
		}
	}
}