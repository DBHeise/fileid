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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e4f8e3b4-0bb7-4100-99ee-1ac53acc9161
				// ptg=0x29 or 0x49 or 0x69
				// The PtgMemFunc mem token specifies that the result of a binary-reference-expression in a mem-area-expression is variable.
				class PtgMemFunc : public PtgSubType {
				private:
					PtgMemFunc(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned short cce;
				public:
					static PtgMemFunc* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgMemFunc* ans = new PtgMemFunc(buffer, max, index);
						index += ans->bytesRead;

						ans->cce = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgMemFunc";
					}
				};
			}
        }
    }
}
