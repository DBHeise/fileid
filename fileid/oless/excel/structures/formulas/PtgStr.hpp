#pragma once
#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "../ShortXLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/87c2a057-705c-4473-a168-6d5fac4a9eba
				// ptg=0x17
				// The PtgStr operand specifies a Unicode string value.
				class PtgStr : public PtgBasic {
				private:
					PtgStr(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					std::string string;
				public:
					static PtgStr* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgStr* ans = new PtgStr(buffer, max, index);
						index += ans->bytesRead;

						auto tmp = ShortXLUnicodeString::Read(buffer, index);
						index += tmp.bytesRead;
						ans->string = tmp.string;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgStr(\"" + this->string + "\")";
					}
				};
			}
        }
    }
}
