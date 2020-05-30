#pragma once

#include "../IParsable.hpp"
#include "../../../common.hpp"


namespace oless {
	namespace excel {
		namespace structures {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/24d30c9e-350e-4d55-a1c3-f4404cc41f99
			// The FormatRun structure specifies formatting information for a text run.
			class FormatRun : public IParseable {
			public:
				unsigned short ich;
				unsigned short ifnt;
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

					this->ich == common::ReadUShort(buffer, max, index);
					index += 2;

					this->ifnt == common::ReadUShort(buffer, max, index);
					index += 2;

					this->bytesRead = index - offset;
				}
			};

		}
	}
}