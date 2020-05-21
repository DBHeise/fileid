#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/62a57ab3-11b5-45df-9d92-0a712d94937a
			// The ColElfU structure specifies the zero-based index of a column in a sheet and relative reference information for this column index and a corresponding row index.
			class ColElfU : public IParseable {
			public:
				unsigned short col : 14;
				unsigned char fQuoted : 1;
				unsigned char fRelative : 1;

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->col = common::ReadUShort(buffer, max, index) << 1 >> 1;
					this->fQuoted = common::ExtractBits(buffer[index + 1], 1, 6);
					this->fRelative = common::ExtractBits(buffer[index + 1], 1, 7);

                    this->bytesRead = 2;
                }
            };
        }
    }
}
