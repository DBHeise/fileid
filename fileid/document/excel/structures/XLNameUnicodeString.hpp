#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/46367a3d-0382-4c32-8373-6ba36229c2c3
			// The XLNameUnicodeString structure specifies a defined name.
			class XLNameUnicodeString {
			private:
				XLNameUnicodeString() {};
			public:
				static XLNameUnicodeString Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					throw std::runtime_error("Not Implemented!");
				}
			};
        }
    }
}
