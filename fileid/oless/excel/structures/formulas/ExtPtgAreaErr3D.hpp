#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/55d25224-b32b-499e-9287-9d429f2276a6
				class ExtPtgAreaErr3D : public IParseable {
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