#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

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
			}
		}
	}
}