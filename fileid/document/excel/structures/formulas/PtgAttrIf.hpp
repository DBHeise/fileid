#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d81e5fb4-3004-409a-9a31-1a60662d9e59
				// ptg=0x19
				// The PtgAttrIf structure specifies a control token.
				class PtgAttrIf : public PtgBasic {
				private:
					unsigned char reserved2 : 1;
					unsigned char bitIf : 1;
					unsigned reserved3 : 6;
					unsigned short offset;
				public:
					PtgAttrIf(unsigned char* buffer, size_t max, unsigned int offset) :reserved2(0), bitIf(0), reserved3(0), offset(0), PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;
					
						this->reserved2 = common::ExtractBits(buffer[index], 1, 1);
						this->bitIf = common::ExtractBits(buffer[index], 1, 2);
						this->reserved3 = common::ExtractBits(buffer[index], 6, 3);
						index++;

						this->offset = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgAttrIf";
					}
				};
			}
		}
	}
}
