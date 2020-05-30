#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1e9eb7d3-0cd8-42a3-af1e-f523105a5e93
			class VertAlign : public IParseable {
			public:
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
