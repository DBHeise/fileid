#pragma once

#include "../ColRelNegU.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {
				using namespace structures;

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/2db37ba7-32f3-4395-88fe-6646034a5358
				// ptg=
				// The RgceLocRel structure specifies a single cell reference where the relative portions of relative references are specified as offsets from the cell in which the formula (section 2.2.2) is evaluated.
				class RgceLocRel {
				public:
					unsigned short row;
					ColRelNegU col;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						this->row = buffer[offset];
						this->col.Parse(buffer, offset, max);
					}
				};
			}
		}
	}
}