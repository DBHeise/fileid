#pragma once

#include "../../common.hpp"

namespace OleStructuredStorage {
	namespace Excel {

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

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/173d9f51-e5d3-43da-8de2-be7f22e119b9
		// The XLUnicodeRichExtendedString structure specifies a Unicode string, which can contain formatting information and phonetic string data.
		class XLUnicodeRichExtendedString {
		private:
			XLUnicodeRichExtendedString() {};
		public:
			static XLUnicodeRichExtendedString Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

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

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/46367a3d-0382-4c32-8373-6ba36229c2c3
		// The XLNameUnicodeString structure specifies a defined name.
		class XLNameUnicodeString {
		private:
			XLNameUnicodeString() {};
		public:
			static XLNameUnicodeString Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

	}
}