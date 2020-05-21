#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "Rgce.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// Base Class for all *ParsedFormula classes
				class ParsedFormulaBase : public IParseable {
				protected:
					unsigned short cce;
					Rgce rgce;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->cce = common::ReadUShort(buffer, max, index, true);
						index += 2;

						this->rgce.Parse(buffer, max, index);
						index += this->rgce.bytesRead;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}
