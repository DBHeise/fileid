#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"

#include "ExtSheetPair.hpp"
#include "RgceAreaRel.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d069151f-2340-4a86-9a40-372659b9baa9
				//The ExtPtgArea3D structure is a variation of PtgArea3d that is used by formulas in an external defined name. It specifies a rectangular cell range on one or more sheet.
				class ExtPtgArea3D : public IParseable {
				private:
					ExtSheetPair iTabs;
					RgceAreaRel area;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->iTabs.Parse(buffer, max, offset);
						index += this->iTabs.bytesRead;

						this->area.Parse(buffer, max, offset);
						index += this->area.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}