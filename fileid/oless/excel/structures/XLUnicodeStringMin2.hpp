#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/55986248-f55f-4010-b5cc-d79d4efbcba0
			// The XLUnicodeStringMin2 structure specifies a Unicode string.
			class XLUnicodeStringMin2 {
			private:
				XLUnicodeStringMin2() {};
			public:
				static XLUnicodeStringMin2 Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					throw std::exception("Not Implemented!");
				}
			};

        }
    }
}
