#pragma once
#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9ded1bd9-4881-4b77-b32f-c77b93df03fd
				class XtiIndex : public IParseable {
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
