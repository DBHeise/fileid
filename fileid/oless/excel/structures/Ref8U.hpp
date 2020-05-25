#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/809af298-1e4f-499f-9bca-3cd1021f4934
			// The Ref8U structure specifies a range of cells on the sheet.
			class Ref8U : public IParseable {
			public:
				unsigned short rwFirst;
				unsigned short rwLast;
				unsigned short colFirst;
				unsigned short colLast;
				std::string to_string() const {
					std::ostringstream ss;
					ss << ColNumToName(this->colFirst + 1) << this->rwFirst + 1 << ":" << ColNumToName(this->colLast + 1) << this->rwLast + 1;
					return ss.str();
				}

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {

					this->rwFirst = common::ReadUShort(buffer, max, offset);
					this->rwLast = common::ReadUShort(buffer, max, offset + 2);
					this->colFirst = common::ReadUShort(buffer, max, offset + 4);
					this->colLast = common::ReadUShort(buffer, max, offset + 6);

                    this->bytesRead = 8;
                }
            };
        }
    }
}
