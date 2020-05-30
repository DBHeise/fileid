#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/167409e7-9363-4b61-9434-47e559e80f2d
				// ptg=0x18
				// The PtgElfColV natural language formula operand specifies a value class reference to a range within a column which is represented by a single-cell natural language label.
				class PtgElfColV : public PtgBasic_elf {
				private:
					
				public:
					PtgElfColV(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic_elf() { 
						this->Parse(buffer, max, offset); 
					}					

					std::string to_string() const override {
						return "PtgElfColV";
					}
				};
			}
		}
	}
}
