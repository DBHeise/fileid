#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/05162858-0ca9-44cb-bb07-a720928f63f8
			// The ShortXLUnicodeString structure specifies a Unicode string.
			class ShortXLUnicodeString {
			private:
				ShortXLUnicodeString() {};
				unsigned char cch;
				unsigned short fHighByte : 1;
				unsigned short reserved1 : 7;
			public:
				std::string string;
				unsigned int bytesRead = 0;
				static ShortXLUnicodeString Read(const unsigned char* buffer, const unsigned int offset) {

					ShortXLUnicodeString ans;
					unsigned int index = offset;

					ans.cch = buffer[index];
					index += 1;

					ans.fHighByte = buffer[index] & 128;
					ans.reserved1 = buffer[index] & 127;
					index++;

					int byteCount = 0;
					if (ans.fHighByte == 0x0) {
						byteCount = ans.cch;
					}
					else {
						byteCount = ans.cch * 2;
					}

					std::string name(reinterpret_cast<char const*>(buffer + index), byteCount);
					ans.bytesRead = index + byteCount;
					ans.string = name;

					return ans;
				}
			};

        }
    }
}
