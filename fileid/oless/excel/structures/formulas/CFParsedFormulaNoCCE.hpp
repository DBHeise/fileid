#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "ParsedFormulaBase.hpp"
#include "Rgce.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d7926ace-9fbf-49b6-8b0c-7502f38c1d97
				class CFParsedFormulaNoCCE : public ParsedFormulaBase {
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->rgce.Parse(buffer, max, index);
						index += this->rgce.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}
