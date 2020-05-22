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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d81e5fb4-3004-409a-9a31-1a60662d9e59
				// ptg=0x19
				// The PtgAttrIf structure specifies a control token.
				class PtgAttrIf : public PtgBasic {
				private:
					PtgAttrIf(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 1;
					unsigned char bitIf : 1;
					unsigned reserved3 : 6;
					unsigned short offset;
				public:
					static PtgAttrIf* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrIf* ans = new PtgAttrIf(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = common::ExtractBits(buffer[index], 1, 1);
						ans->bitIf = common::ExtractBits(buffer[index], 1, 2);
						ans->reserved3 = common::ExtractBits(buffer[index], 6, 3);
						index++;

						ans->offset = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrIf";
					}
				};
			}
		}
	}
}
