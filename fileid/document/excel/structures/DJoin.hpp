#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/104e4ca1-6f15-4c6a-9f61-d6a590be4836
			class DJoin : public IParseable {
			public:
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
