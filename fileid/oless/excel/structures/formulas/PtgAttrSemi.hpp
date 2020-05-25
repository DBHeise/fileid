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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/615c5518-010a-4268-b71b-b60074bdb11b
				// ptg=0x19
				// The PtgAttrSemi structure specifies that this Rgce is volatile.
				class PtgAttrSemi : public PtgBasic {
				private:
					unsigned char bitSemi : 1;
					unsigned reserved2 : 7;
					unsigned short unused;
				public:
					PtgAttrSemi(unsigned char* buffer, size_t max, unsigned int offset): bitSemi(0), reserved2(0), unused(0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->bitSemi = common::ExtractBits(buffer[index], 1, 1);
						this->reserved2 = common::ExtractBits(buffer[index], 7, 2);
						index++;

						this->unused = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}					
					std::string to_string() const override {
						return "PtgAttrSemi";
					}
				};
			}
		}
	}
}
