#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5adbad90-093d-4bc6-acc1-b662270bc0d7
			//The XTI structure specifies a supporting linkand scope information about that supporting link.
			class XTI : public IParseable {
			public:
				unsigned short iSupBook;
				signed short iTabFirst;
				signed short iTabLast;

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->iSupBook = common::ReadUShort(buffer, max, index);
					index += 2;

					this->iTabFirst = common::ReadSShort(buffer, max, index);
					index += 2;

					this->iTabLast = common::ReadSShort(buffer, max, index);
					index += 2;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
