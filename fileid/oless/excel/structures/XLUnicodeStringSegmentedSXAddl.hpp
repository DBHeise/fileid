#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/18afd490-6901-4d3d-a8de-38898a3724a0
			// The XLUnicodeStringSegmentedSXAddl structure specifies a Unicode string segment.
			class XLUnicodeStringSegmentedSXAddl {
			private:
				XLUnicodeStringSegmentedSXAddl() {};
			public:
				static XLUnicodeStringSegmentedSXAddl Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					throw std::exception("Not Implemented!");
				}
			};
        }
    }
}
