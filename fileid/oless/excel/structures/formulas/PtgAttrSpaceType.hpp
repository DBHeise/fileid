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

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/3ba6adc8-2581-4758-b322-29718f8ed125
				// The PtgAttrSpaceType structure specifies the number of space or carriage return characters and position of those characters.
				struct PtgAttrSpaceType {
					unsigned char type;
					unsigned char cch;
					void Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						if (offset + 1 <= max) {
							this->type = buffer[offset];
							this->cch = buffer[offset + 1];
						}
					}
				};
			}
		}
	}
}