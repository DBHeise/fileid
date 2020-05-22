#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
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
					PtgAttrSpace(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 6;
					unsigned char bitSpace : 1;
					unsigned char reserved3 : 1;
					PtgAttrSpaceType type;
				public:
					static PtgAttrSpace* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrSpace* ans = new PtgAttrSpace(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = common::ExtractBits(buffer[index], 1, 1);
						ans->bitSpace = common::ExtractBits(buffer[index], 1, 2);
						ans->reserved3 = common::ExtractBits(buffer[index], 6, 3);
						index++;

						ans->type.Parse(buffer, max, index);
						index += ans->type.bytesRead;

						ans->bytesRead = offset - index;
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrSpace";
					}
				};
			}
		}
	}
}