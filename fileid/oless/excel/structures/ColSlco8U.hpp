#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/17150e2d-96e0-499a-8b23-b1d99ee42e85
			class ColSlco8U : public IParseable {
			public:
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
