#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"
#include "../ColRelNegU.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {
				using namespace structures;

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/2db37ba7-32f3-4395-88fe-6646034a5358
				// ptg=
				// The RgceLocRel structure specifies a single cell reference where the relative portions of relative references are specified as offsets from the cell in which the formula (section 2.2.2) is evaluated.
				class RgceLocRel: public IParseable {
				public:
					unsigned short row;
					ColRelNegU col;
					
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->row = common::ReadUShort(buffer, max, index);
						index += 2;

						this->col.Parse(buffer, max,offset);
						index += this->col.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}