#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "PtgAttrSpaceType.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/38a4d7be-040b-4206-b078-62f5aeec72f3
				// ptg=0x19
				// The PtgAttrSpace display token specifies a number of space or carriage return characters that are displayed around the expression in a display-precedence-expression.
				class PtgAttrSpace : public PtgBasic {
				private:
					
					unsigned char reserved2 : 6;
					unsigned char bitSpace : 1;
					unsigned char reserved3 : 1;
					PtgAttrSpaceType type;
				public:
					PtgAttrSpace(unsigned char* buffer, size_t max, unsigned int offset): reserved2(0), bitSpace(0), reserved3(0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->reserved2 = common::ExtractBits(buffer[index], 1, 1);
						this->bitSpace = common::ExtractBits(buffer[index], 1, 2);
						this->reserved3 = common::ExtractBits(buffer[index], 6, 3);
						index++;

						this->type.Parse(buffer, max, index);
						index += this->type.bytesRead;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgAttrSpace";
					}
				};
			}
		}
	}
}