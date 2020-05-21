#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/36ca6de7-be16-48bc-aa5e-3eaf4942f671
			// The XLUnicodeString structure specifies a Unicode string.
			class XLUnicodeString {
			private:
				XLUnicodeString() {};
				unsigned short cch;
				unsigned short fHighByte : 1;
				unsigned short reserved1 : 7;
			public:
				std::string string;
				unsigned int bytesRead = 0;

				static XLUnicodeString Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					XLUnicodeString ans;
					unsigned int index = offset;

					ans.cch = common::ReadUShort(buffer, max, index);
					index += 2;

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

					if (byteCount > max) {
						byteCount = max;
					}
					std::string name(reinterpret_cast<char const*>(buffer + index), byteCount);

					ans.string = name;
					ans.bytesRead = (index - offset) + byteCount;

					return ans;
				}
			};

        }
    }
}
