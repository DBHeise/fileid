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

					ans.fHighByte = common::ExtractBits(buffer[index], 1, 1);
					ans.reserved1 = common::ExtractBits(buffer[index], 7, 2);
					index++;

					int byteCount = ans.cch;
					if (ans.fHighByte == 0x0) {
						std::string name(reinterpret_cast<char const*>(buffer + index), byteCount);
						ans.string = name;
					}
					else {
						std::wstring wname(reinterpret_cast<wchar_t const*>(buffer + index), byteCount);
						ans.string = common::convert(wname);
					}

					
					ans.bytesRead = 2 + byteCount;

					return ans;
				}
			};

        }
    }
}
