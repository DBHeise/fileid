#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1f0b785a-05e8-495a-812d-c7c164840985
			// The XLUnicodeStringSegmentedRTD structure specifies a Unicode string that contains a set of sub-strings.
			class XLUnicodeStringSegmentedRTD {
			private:
				XLUnicodeStringSegmentedRTD() {};
			public:
				static XLUnicodeStringSegmentedRTD Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					throw std::exception("Not Implemented!");
				}
			};
        }
    }
}
