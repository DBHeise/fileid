#pragma once

#include <string>
#include "../../../common.hpp"
#include "../MSExcel.common.hpp"
#include "../IParsable.hpp"

namespace oless {
	namespace excel {
		namespace structures {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6bb50f66-faf0-48f9-b6a9-f0f452a77598
			// The Cell structure specifies a cell in the current sheet.
			class Cell : public IParseable {
			public:
				unsigned short rw;
				unsigned short col;
				unsigned short ixfe;

				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->rw = common::ReadUShort(buffer, max, index);
					index += 2;

					this->col = common::ReadUShort(buffer, max, index);
					index += 2;

					this->ixfe = common::ReadUShort(buffer, max, index);
					index += 2;

					this->bytesRead = index - offset;
				}

				std::string to_string() const {
					std::ostringstream ss;
					ss << ColNumToName(this->col + 1) << this->rw + 1;
					return ss.str();
				}
			};
		}
	}
}