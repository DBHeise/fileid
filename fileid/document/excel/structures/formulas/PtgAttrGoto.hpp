#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/081e17b9-02a6-4e78-ad28-09538f35a312
				// ptg=0x19
				// The PtgAttrGoto structure specifies a control token.
				class PtgAttrGoto : public PtgBasic {
				private:					
					unsigned char reserved2 : 3;
					unsigned char bitGoto : 1;
					unsigned char reserved3 : 4;
					unsigned short offset;
				public:
					PtgAttrGoto(unsigned char* buffer, size_t max, unsigned int offset): reserved2(0), bitGoto(0), reserved3(0), offset(0), PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->reserved2 = common::ExtractBits(buffer[index], 3, 1);
						this->bitGoto = common::ExtractBits(buffer[index], 1, 4);
						this->reserved3 = common::ExtractBits(buffer[index], 4, 5);
						index++;

						this->offset = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = 4;
					}

					std::string to_string() const override {
						return "PtgAttrGoto";
					}
				};
			}
		}
	}
}