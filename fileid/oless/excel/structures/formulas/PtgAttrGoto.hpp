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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/081e17b9-02a6-4e78-ad28-09538f35a312
				// ptg=0x19
				// The PtgAttrGoto structure specifies a control token.
				class PtgAttrGoto : public PtgBasic {
				private:
					PtgAttrGoto(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 3;
					unsigned char bitGoto : 1;
					unsigned char reserved3 : 4;
					unsigned short offset;
				public:
					static PtgAttrGoto* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrGoto* ans = new PtgAttrGoto(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = common::ExtractBits(buffer[index], 3, 1);
						ans->bitGoto = common::ExtractBits(buffer[index], 1, 4);
						ans->reserved3 = common::ExtractBits(buffer[index], 4, 5);
						index++;

						ans->offset = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = offset - index;
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrGoto";
					}
				};
			}
		}
	}
}