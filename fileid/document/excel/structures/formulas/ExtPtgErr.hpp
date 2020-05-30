#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6037ca97-0e46-48e0-9de8-8527f345b549
				// The PtgErr operand specifies an error code.
				class ExtPtgErr : public IParseable {
				private:
					unsigned char ptg : 7;
					unsigned char A : 1;
					unsigned char err;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->ptg = common::ExtractBits(buffer[index], 7, 1);
						this->A = common::ExtractBits(buffer[index], 1, 8);
						index++;

						this->err = buffer[index];
						index++;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}