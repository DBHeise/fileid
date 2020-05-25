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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/79ef57f6-27ab-4fec-b893-7dd727e771d1
				// ptg=0x19
				// The PtgAttrSum structure specifies the sum of an expression as defined in function-call.
				class PtgAttrSum : public PtgBasic {
				private:
					PtgAttrSum(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 4;
					unsigned char bitSum : 1;
					unsigned char reserved4 : 3;
					unsigned short unused;
				public:
					static PtgAttrSum* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrSum* ans = new PtgAttrSum(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = common::ExtractBits(buffer[index], 4, 1);
						ans->bitSum = common::ExtractBits(buffer[index], 1, 5);
						ans->reserved4 = common::ExtractBits(buffer[index], 3, 6);
						index++;

						ans->unused = common::ReadUShort(buffer, max, index);
						index += 2;
						
						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrSum";
					}
				};
			}
		}
	}
}
