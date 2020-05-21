#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e64abeee-2f3a-4004-b9e3-3d67e29d6066
			// The XLUnicodeStringNoCch structure specifies a Unicode string.
			class XLUnicodeStringNoCch {
			private:
				XLUnicodeStringNoCch() {};
			public:
				static XLUnicodeStringNoCch Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					throw std::exception("Not Implemented!");
				}
			};
        }
    }
}
