#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6e5eed10-5b77-43d6-8dd0-37345f8654ad
			// The ColRelU structure specifies the zero-based index of a column in a sheet and relative reference information for this column index and a corresponding row index.
			class ColRelU : public IParseable {
			public:
				unsigned short col : 14;
				unsigned char colRelative : 1;
				unsigned char rowRelative : 1;
				std::string to_string() const {
					std::ostringstream ss;
					ss << ColNumToName(this->col + 1) << "[" << std::to_string(this->rowRelative) << "," << std::to_string(this->colRelative) << "]";
					return ss.str();
				}

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->col = common::ReadUShort(buffer, max, index) << 1 >> 1;					
					this->colRelative = common::ExtractBits(buffer[index + 1], 1, 6);
					this->rowRelative = common::ExtractBits(buffer[index + 1], 1, 7);

                    this->bytesRead = 2;
                }
            };
        }
    }
}
