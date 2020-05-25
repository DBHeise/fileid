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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6ed51fe3-4baf-4163-8851-888de8477525
				// ptg=0x18
				// The PtgElfColSV natural language formula operand specifies a value class reference to a range within a column that is identified by a multiple-cell natural language label. There MUST be a PtgExtraElf in the RgbExtra corresponding to this PtgElfColSV. The correspondence between PtgElfColSV and PtgExtraElf structures is specified in RgbExtra.
				class PtgElfColSV : public PtgBasic_elf {
				private:
					
				public:
					PtgElfColSV(unsigned char* buffer, size_t max, unsigned int offset) : PtgBasic_elf() {
						this->Parse(buffer, max, offset); 
					}

					std::string to_string() const override {
						return "PtgElfColSV";
					}
				};
			}
		}
	}
}
