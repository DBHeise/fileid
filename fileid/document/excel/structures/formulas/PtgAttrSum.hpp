#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/79ef57f6-27ab-4fec-b893-7dd727e771d1
				// ptg=0x19
				// The PtgAttrSum structure specifies the sum of an expression as defined in function-call.
				class PtgAttrSum : public PtgBasic {
				private:
					
					unsigned char reserved2 : 4;
					unsigned char bitSum : 1;
					unsigned char reserved4 : 3;
					unsigned short unused;
				public:
					PtgAttrSum(unsigned char* buffer, size_t max, unsigned int offset): reserved2(0), bitSum(0), reserved4(0), unused(0), PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->reserved2 = common::ExtractBits(buffer[index], 4, 1);
						this->bitSum = common::ExtractBits(buffer[index], 1, 5);
						this->reserved4 = common::ExtractBits(buffer[index], 3, 6);
						index++;

						this->unused = common::ReadUShort(buffer, max, index);
						index += 2;
						
						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgAttrSum";
					}
				};
			}
		}
	}
}
