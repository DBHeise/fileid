#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/70f743b2-a853-4c57-88be-8af637ac6e43
				class RgbExtra : public IParseable {
					std::vector<uint8_t> data;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;
						data.insert(data.end(), &buffer[index], &buffer[max]);
						this->bytesRead = max - offset;
					}
				};
			}
		}
	}
}
