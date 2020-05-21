#pragma once

#include <string>
#include "../../../common.hpp"
#include "../MSExcel.common.hpp"
#include "../IParsable.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/39a0757a-c7bb-4e85-b144-3e7837b059d7
			// The FormulaValue structure specifies the current value of a formula.
			class FormulaValue : public IParseable {
			public:
				unsigned char byte1;
				unsigned char byte2;
				unsigned char byte3;
				unsigned char byte4;
				unsigned char byte5;
				unsigned char byte6;
				unsigned short fExprO;

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }

				std::string Value() const {
					std::string ans;
					if (this->fExprO == 0xFFFF) {
						switch (this->byte1) {
						case 0x00: //String Value
							break;
						case 0x01: //Boolean Value
							break;
						case 0x02: //Error Value
							break;
						case 0x03: //Blank String
							ans = "";
							break;
						}
					}
					else {
						union {
							unsigned char data[8];
							double num;
						};
						data[0] = this->byte1;
						data[1] = this->byte2;
						data[2] = this->byte3;
						data[3] = this->byte4;
						data[4] = this->byte5;
						data[5] = this->byte6;
						data[6] = this->fExprO;
						data[7] = this->fExprO >> 8;

						/*double num;
						*((unsigned char*)(&num) + 0) = this->byte1;
						*((unsigned char*)(&num) + 1) = this->byte2;
						*((unsigned char*)(&num) + 2) = this->byte3;
						*((unsigned char*)(&num) + 3) = this->byte4;
						*((unsigned char*)(&num) + 4) = this->byte5;
						*((unsigned char*)(&num) + 5) = this->byte6;

						*((unsigned short*)(&num) + 6) = this->fExprO;
						ans = std::to_string(num);
						*/
						ans = std::to_string(num);
					}

					return ans;
				}

            };
        }
    }
}
