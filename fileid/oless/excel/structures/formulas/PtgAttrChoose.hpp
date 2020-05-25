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
					
					unsigned char reserved2 : 2;
					unsigned char bitChoose : 1;
					unsigned char reserved3 : 5;
					unsigned short cOffset;
					std::vector<unsigned short> rgOffset;
				public:
					PtgAttrChoose(unsigned char* buffer, size_t max, unsigned int offset): reserved2(0), bitChoose(0), reserved3(0), cOffset(0), PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->reserved2 = common::ExtractBits(buffer[index], 2, 1);
						this->bitChoose = common::ExtractBits(buffer[index], 1, 3);
						this->reserved3 = common::ExtractBits(buffer[index], 5, 4);
						index++;

						this->cOffset = common::ReadUShort(buffer, max, index);
						index += 2;

						for (unsigned short i = 0; i < this->cOffset; i++) { //TODO: Verify this logic???
							auto tmp = common::ReadUShort(buffer, max, index);
							index += 2;
							this->rgOffset.push_back(tmp);
						}

						this->bytesRead = offset - index;
					}
					
					std::string to_string() const override {
						return "PtgAttrChoose";
					}
				};
			}
		}
	}
}
