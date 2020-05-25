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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fcd76e10-6072-4dcf-b591-47edc8822792
				// ptg=0x19
				// The PtgAttrBaxcel structure specifies that the result of the Rgce is to be assigned to a local variable used in a macro sheet.
				class PtgAttrBaxcel : public PtgBasic {
				private:
					PtgAttrBaxcel(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char bitSemi : 1;
					unsigned char reserved2 : 4;
					unsigned char bitBaxcel : 1;
					unsigned char reserved3 : 2;
					unsigned short unused;
				public:
					static PtgAttrBaxcel* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrBaxcel* ans = new PtgAttrBaxcel(buffer, max, index);
						index += ans->bytesRead;

						ans->bitSemi = common::ExtractBits(buffer[index], 1, 1);
						ans->reserved2 = common::ExtractBits(buffer[index], 4, 2);
						ans->bitBaxcel = common::ExtractBits(buffer[index], 1, 6);
						ans->reserved3 = common::ExtractBits(buffer[index], 2, 7);
						index++;

						ans->unused = common::ReadUShort(buffer, max, index);
						index += 2;
						
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrBaxcel";
					}
				};

			}
		}
	}
}