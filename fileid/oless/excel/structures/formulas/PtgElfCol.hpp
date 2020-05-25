#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/c76517f7-6a4e-47e8-8087-6e927758bbed
				// ptg=0x18
				// The PtgElfCol natural language formula operand specifies a reference class reference to a range within a column which is represented by a single-cell natural language label.
				class PtgElfCol : public PtgBasic_elf {
				private:
					
				public:
					PtgElfCol(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic_elf() { 
						this->Parse(buffer, max, offset);
					}

					std::string to_string() const override {
						return "PtgElfCol";
					}
				};
			}
		}
	}
}