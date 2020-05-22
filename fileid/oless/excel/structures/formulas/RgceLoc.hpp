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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f2395c33-34a4-4b07-85a9-9bb5f07848d9
				// ptg=
				// The RgceLoc structure specifies a reference to a single cell where relative references are stored as coordinates.
				class RgceLoc : public IParseable {
				public:
					unsigned short row;
					ColRelU col;
					std::string to_string() const {
						std::ostringstream ss;
						ss << ColNumToName(this->col.col + 1) << this->row + 1;
						return ss.str();
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						unsigned index = offset;
						
						this->row = common::ReadUShort(buffer, max, index);
						index += 2;

						this->col.Parse(buffer, max, index);
						index += this->col.bytesRead;
						
						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}
