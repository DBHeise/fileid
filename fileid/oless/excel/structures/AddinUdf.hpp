#pragma once

#include <string>
#include "../../../common.hpp"
#include "../IParsable.hpp"

#include "ShortXLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace structures {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/3adbcd79-0922-41cd-9778-ee8f8ce031a4
			class AddinUdf : public IParseable {
			private:
				unsigned int reserved;

			public:
				std::string udfName;
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;


					this->reserved = common::ReadUInt(buffer, max, index, true);
					index += 4;

					auto s = excel::structures::ShortXLUnicodeString::Read(buffer, index);
					index += s.bytesRead;
					this->udfName = s.string;


                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
