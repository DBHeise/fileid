#pragma once

#include "../../../../common.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fcd76e10-6072-4dcf-b591-47edc8822792
				// ptg=0x19
				// The PtgAttrBaxcel structure specifies that the result of the Rgce is to be assigned to a local variable used in a macro sheet.
				class PtgAttrBaxcel : public PtgBasic {
				private:
					
					unsigned char bitSemi : 1;
					unsigned char reserved2 : 4;
					unsigned char bitBaxcel : 1;
					unsigned char reserved3 : 2;
					unsigned short unused;
				public:
					PtgAttrBaxcel(unsigned char* buffer, size_t max, unsigned int offset): bitSemi(0), reserved2(0), bitBaxcel(0), reserved3(0), unused(0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

											
						this->bitSemi = common::ExtractBits(buffer[index], 1, 1);
						this->reserved2 = common::ExtractBits(buffer[index], 4, 2);
						this->bitBaxcel = common::ExtractBits(buffer[index], 1, 6);
						this->reserved3 = common::ExtractBits(buffer[index], 2, 7);
						index++;

						this->unused = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = offset - index;
					}

					std::string to_string() const override {
						return "PtgAttrBaxcel";
					}
				};

			}
		}
	}
}