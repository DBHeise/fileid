#pragma once

#include "MSExcel.strings.hpp"

namespace OleStructuredStorage {
	namespace Excel {


		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/69ff31ac-671b-4aaf-a3b5-a01e9e283a03
		// The SerAr structure specifies a cell value within an array of values.
		class SerAr {
		public:			
			static SerAr* Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fa735454-09d8-4982-a5fb-dabaa9f02d5d
		// The SerNil structure specifies a null value in an array of values.
		class SerNil : public SerAr {
		public:
			unsigned char reserved1; //0x0
			unsigned int unused1;
			unsigned int unused2;
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7a876271-cde6-4b80-a35e-ceddf65aedba
		// The SerNum structure specifies a numeric value in an array of values.
		class SerNum : public SerAr {
		public:
			unsigned char reserved1; //0x1
			double xnum;
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8a7db24e-bcd5-49e7-af94-c7ccb2087f23
		// The SerStr structure specifies a string in an array of values.
		class SerStr : public SerAr {
		private:
			unsigned char reserved1; //0x2			
		public:
			std::string string;

			static SerStr Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				SerStr ans;
				ans.reserved1 = buffer[offset];
				ans.string = XLUnicodeString::Read(buffer, offset + 1, max).string;
				return ans;
			}
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8c22e17f-0f97-4597-b2bd-7a2f5ddfc72d
		// The SerBool structure specifies a Boolean (section 2.5.14) value in an array of values.
		class SerBool : public SerAr {
		public:
			unsigned char reserved1; //0x4
			unsigned char f;
			unsigned char reserved2;
			unsigned short unused1;
			unsigned int unused2;
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/153fddfb-8c8a-4d6d-9e51-d0940244e5b4
		// The SerErr structure specifies an error value in an array of values.
		class SerErr : public SerAr {
		public:
			unsigned char reserved1; //0x10
			unsigned char err;
			unsigned char reserved2;
			unsigned short unused1;
			unsigned int unused2;
		};
	}
}
