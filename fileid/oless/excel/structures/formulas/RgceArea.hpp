#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "../ColRelU.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6df491b9-14e8-4efd-9d92-98db51b7cdbd
				// The RgceArea structure specifies a reference to a rectangular range of cells where relative references are stored as coordinates. 
				class RgceArea : public IParseable {
				public:
					unsigned short rowFirst;
					unsigned short rowLast;
					ColRelU columnFirst;
					ColRelU columnLast;
					std::string to_string() const {
						std::ostringstream ss;
						ss << ColNumToName(this->columnFirst.col + 1) << this->rowFirst + 1 << ":" << ColNumToName(this->columnLast.col + 1) << this->rowLast + 1;
						return ss.str();
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->rowFirst = common::ReadUShort(buffer, max, index);
						index += 2;

						this->rowLast = common::ReadUShort(buffer, max, index);
						index += 2;

						this->columnFirst.Parse(buffer, max, index);
						index += 2;

						this->columnLast.Parse(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}
