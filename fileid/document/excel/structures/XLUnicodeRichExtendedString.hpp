#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/173d9f51-e5d3-43da-8de2-be7f22e119b9
			// The XLUnicodeRichExtendedString structure specifies a Unicode string, which can contain formatting information and phonetic string data.
			class XLUnicodeRichExtendedString {
			private:
				unsigned short cch;
				unsigned short fHighByte : 1;
				unsigned short reserved1 : 1;
				unsigned short fExtSt : 1;
				unsigned short fRichSt : 1;
				unsigned short reserved2 : 4;
				unsigned short cRun;
				int cbExtRst;
				std::string rgb;
				XLUnicodeRichExtendedString() {};
			public:
				unsigned int bytesRead = 0;
				std::string String() {
					return this->rgb;
				}
				static XLUnicodeRichExtendedString Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					XLUnicodeRichExtendedString ans;
					unsigned int index = offset;

					ans.cch = common::ReadUShort(buffer, max, index);
					index += 2;

					ans.fHighByte = common::ExtractBits(buffer[index], 1, 1);
					ans.reserved1 = common::ExtractBits(buffer[index], 1, 2);
					ans.fExtSt = common::ExtractBits(buffer[index], 1, 3);
					ans.fRichSt = common::ExtractBits(buffer[index], 1, 4);
					ans.reserved2 = common::ExtractBits(buffer[index], 4, 5);
					index++;

					if (ans.fRichSt == 0x1) {
						ans.cRun = common::ReadUShort(buffer, max, index);
						index += 2;
					}
					if (ans.fExtSt == 0x1) {
						ans.cbExtRst = common::ReadSInt(buffer, max, index);
						index += 4;
					}

					int byteCount = ans.cch;

					//TODO: ensure we don't read past the end of the buffer
					if (ans.fHighByte == 0x0) {
						std::string name(reinterpret_cast<char const*>(buffer + index), byteCount);
						ans.rgb = name;
						index += byteCount;
					} else {						
						std::wstring wname(reinterpret_cast<wchar_t const*>(buffer + index), byteCount);
						ans.rgb = common::erasenulls(common::convert(wname));
						index += (byteCount*2);
					}


					if (ans.fRichSt == 0x1) {
						//TODO: Read array of FormatRun structures
					}

					if (ans.fExtSt == 0x1) {
						//TODO: Read ExtRst
					}

					ans.bytesRead = index - offset;
					return ans;
				}
			};

        }
    }
}
