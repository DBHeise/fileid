#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "../ColElfU.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/231fcf3f-9bb2-49dd-b97d-d9389188dc5e
				// The RgceElfLoc structure specifies a location of a cell that contains a label used in a natural language formula to refer to a contiguous range of cells from the same row or column as the cell with the label.
				class RgceElfLoc {
				public:
					unsigned short row;
					ColElfU col;
					void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) {
						this->row = common::ReadUShort(buffer, max, offset);
						this->col.Parse(buffer, max, offset + 2);
					}
				};
			}
		}
	}
}
