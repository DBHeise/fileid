#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/ebf366bb-b39b-453f-a2c7-b27d53d8e43f
				class ExtPtgRefErr3D : public IParseable {
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