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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f225058b-61ef-4a94-8f58-1195d8087849
				// ptg=
				// The RgceElfLocExtra structure specifies a single cell reference which specifies a part of a multiple-cell natural language label. The cell is specified as the intersection of the given row and column. 
				class RgceElfLocExtra {
				public:
					unsigned short row;
					ColRelU col;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						this->row = common::ReadUShort(buffer, max, offset);
						this->col.Parse(buffer, offset + 2, max);
					}
				};
			}
		}
	}
}
