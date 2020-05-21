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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/24fb579c-c65d-4771-94a8-4380cecdc8c8
				// ptg=0x19
				// The PtgAttrChoose structure specifies a control token.
				class PtgAttrChoose : public PtgBasic {
				private:
					PtgAttrChoose(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 2;
					unsigned char bitChoose : 1;
					unsigned char rserved3 : 5;
					unsigned short cOffset;
					unsigned short* rgOffset;
				public:
					static PtgAttrChoose* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgAttrChoose* ans = new PtgAttrChoose(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 2 + this->cOffset; }
					std::string to_string() const override {
						return "PtgAttrChoose";
					}
				};
			}
		}
	}
}
