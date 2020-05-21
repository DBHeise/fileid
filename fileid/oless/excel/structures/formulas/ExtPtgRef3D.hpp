#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/03b41fde-9697-4220-96c7-e2c86cedb30e
				class ExtPtgRef3D : public IParseable {
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}