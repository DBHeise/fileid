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
					PtgAttrSemi(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char bitSemi : 1;
					unsigned reserved2 : 7;
					unsigned short unused;
				public:
					static PtgAttrSemi* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrSemi* ans = new PtgAttrSemi(buffer, max, offset);
						index++;

						ans->bitSemi = common::ExtractBits(buffer[index], 1, 1);
						ans->reserved2 = common::ExtractBits(buffer[index], 7, 2);
						index++;

						ans->unused = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}					
					std::string to_string() const override {
						return "PtgAttrSemi";
					}
				};
			}
		}
	}
}
