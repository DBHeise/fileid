#pragma once

#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "../ColRelNegU.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/75afd109-b1ce-4511-b56f-2d63116f6647
				// The RgceAreaRel structure specifies a rectangular range of cells where the relative portions of relative references are specified as offsets from the cell in which the formula (section 2.2.2) is evaluated.
				class RgceAreaRel: public IParseable {
				public:
					unsigned short rowFirst;
					unsigned short rowLast;
					ColRelNegU columnFirst;
					ColRelNegU columnLast;

					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						this->rowFirst = common::ReadUShort(buffer, max, offset);
						this->rowLast = common::ReadUShort(buffer, max, offset + 2);
						this->columnFirst.Parse(buffer, max, offset + 4);
						this->columnLast.Parse(buffer, max, offset + 6);

						this->bytesRead = 8;
					}
				};
			}
		}
	}
}
