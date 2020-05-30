#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

#include "XLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/796bcbeb-f2eb-49ee-86a3-518f65db3aa0
			// The XLUnicodeStringSegmented structure specifies a Unicode string that is split into multiple string segments. 
			class XLUnicodeStringSegmented {
			private:
				XLUnicodeStringSegmented() {};
				unsigned int cchTotal;
				std::vector<std::string> strings;
			public:
				unsigned int bytesRead = 0;

				static XLUnicodeStringSegmented Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
					XLUnicodeStringSegmented ans;
					int index = offset;

					ans.cchTotal = common::ReadUInt(buffer, max, index);
					ans.bytesRead = 4;
					index += 4;

					if (ans.cchTotal >= 2147483644) {
						//?
					}

					int chCount = 0;

					while (chCount < ans.cchTotal && ans.bytesRead < max) {
						auto str = XLUnicodeString::Read(buffer, index, max);
						ans.bytesRead += str.bytesRead;
						index += str.bytesRead;
						ans.strings.push_back(str.string);
						chCount += str.string.length();
					}

					return ans;
				}
				std::string ToOneString() {
					std::ostringstream str;
					for (const auto& substr : this->strings) {
						str << substr;
					}
					return str.str();
				}
			};

        }
    }
}
