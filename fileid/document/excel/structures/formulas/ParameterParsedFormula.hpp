#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fb169139-70a4-4562-8b9f-7f3722f589b6
			class ParameterParsedFormula : public IParseable {
			public:
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
