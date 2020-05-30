#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

            // see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/ba60ac38-4312-4ae9-892a-0a0687b82d4d
			class ListParsedFormula : public IParseable {
			public:
				virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
					unsigned int index = offset;

                    this->bytesRead = index - offset;
                }
            };
        }
    }
}
