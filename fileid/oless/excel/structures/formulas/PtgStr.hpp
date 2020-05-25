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
					std::string string;
				public:
					PtgStr(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset); 
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						auto tmp = ShortXLUnicodeString::Read(buffer, index);
						index += tmp.bytesRead;
						this->string = tmp.string;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgStr(\"" + this->string + "\")";
					}
				};
			}
        }
    }
}
