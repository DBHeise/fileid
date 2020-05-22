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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5d8c3df5-9be5-46d9-8105-a1a19ceca3d4
				// ptg=0x19
				// The PtgAttrSpaceSemi structure specifies a number of space or carriage return characters that are displayed around the expression in a display-precedence-specifier and that the Rgce is volatile.
				class PtgAttrSpaceSemi : public PtgBasic {
				private:
					PtgAttrSpaceSemi(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2;
					PtgAttrSpaceType type;
				public:
					static PtgAttrSpaceSemi* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrSpaceSemi* ans = new PtgAttrSpaceSemi(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = buffer[index];
						index++;

						ans->type.Parse(buffer, max, index);
						index += ans->type.bytesRead;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgAttrSpaceSemi";
					}
				};
			}
		}
	}
}