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
			class XLUnicodeStringNoCch : public IParseable {
			private:
				unsigned short fHighByte : 1;
				unsigned short reserved1 : 7;

				short size = -1;

			public:
				std::string string;
				unsigned int bytesRead = 0;
				XLUnicodeStringNoCch(const unsigned char* buffer, const std::size_t max, const unsigned int offset, const unsigned char size) 
				{
					this->size = size;
					this->Parse(const_cast<unsigned char*>(buffer), max, offset);
				}
				virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
					if (this->size < 0)
						throw new std::invalid_argument("Must set size before calling Parse (see cTor)");

					unsigned int index = offset;

					if (index <= max) {
						this->fHighByte = common::ExtractBits(buffer[index], 1, 1);
						this->reserved1 = common::ExtractBits(buffer[index], 7, 2);
						index++;
					}

					if (this->fHighByte == 0x0) {
						if (index + size <= max) {
							std::string name(reinterpret_cast<char const*>(buffer + index), size);
							this->string = name;
							index += size;
						}
					}
					else {
						if (index + (size * 2) <= max) {
							std::wstring wname(reinterpret_cast<wchar_t const*>(buffer + index), size * 2);
							this->string = common::convert(wname);
							index += size * 2;
						}
					}

					this->bytesRead = index - offset;
				}

				static XLUnicodeStringNoCch Read(const unsigned char* buffer, const std::size_t max, const unsigned int offset, const unsigned char size) {
					return XLUnicodeStringNoCch(buffer, max, offset, size);
				}
			};
        }
    }
}
