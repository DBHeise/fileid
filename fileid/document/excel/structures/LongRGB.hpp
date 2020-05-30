#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"
#include "../MSExcel.common.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/dfedc142-44ef-4981-b6c6-50d607abf756
			class LongRGB : public IParseable, public common::IExportable {
			private:
			public:
				unsigned char red;
				unsigned char green;
				unsigned char blue;
				unsigned char reserved;

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->red = buffer[index];
					index++;
					this->green = buffer[index];
					index++;
					this->blue = buffer[index];
					index++;
					this->reserved = buffer[index];
					index++;
                    this->bytesRead = index - offset;
                }

				virtual std::string ToXml() const {
					std::ostringstream str;
					str << "<LongRGB>";
					str << "<red>" << (unsigned short)this->red << "</red>";
					str << "<green>" << (unsigned short)this->green << "</green>";
					str << "<blue>" << (unsigned short)this->blue << "</blue>";
					str << "<reserved>" << (unsigned short)this->reserved << "</reserved>";
					str << "</LongRGB>";
					return str.str();
				}
				virtual std::string ToJson() const {
					std::ostringstream str;
					str << "{";
					str << "\"red\":" << (unsigned short)this->red;
					str << ",\"green\":" << (unsigned short)this->green;
					str << ",\"blue\":" << (unsigned short)this->blue;
					str << ",\"reserved\":" << (unsigned short)this->reserved;
					str << "}";
					return str.str();
				}
				virtual std::string ToCsv() const { 
					std::ostringstream str;
					str << (unsigned short)this->red << "," << (unsigned short)this->green << ","<< (unsigned short)this->blue << "," << (unsigned short)this->reserved;
					return str.str();
				}
				virtual std::string ToText() const { 
					std::ostringstream str;
					str << "#";
					str << std::setfill('0') << std::uppercase;
					str << std::hex << std::setw(2) << (unsigned short)this->red;
					str << std::hex << std::setw(2) << (unsigned short)this->green;
					str << std::hex << std::setw(2) << (unsigned short)this->blue;
					str << std::hex << std::setw(2) << (unsigned short)this->reserved;
					return str.str();
				}
            };
        }
    }
}
