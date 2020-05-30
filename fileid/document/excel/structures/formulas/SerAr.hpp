#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/69ff31ac-671b-4aaf-a3b5-a01e9e283a03
				// The SerAr structure specifies a cell value within an array of values.
				class SerAr : public IParseable {
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;
						this->bytesRead = index - offset;

						throw std::runtime_error("Not Implemented!");
					}
				};
			}
		}
	}
}
