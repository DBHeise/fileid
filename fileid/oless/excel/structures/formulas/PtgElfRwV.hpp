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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/42e28815-da53-45ba-80f2-2a68ddbbfcf9
				// ptg=0x18
				// The PtgElfRwV natural language formula operand specifies a value class reference to a range within a row which is represented by a single-cell natural language label.
				class PtgElfRwV : public PtgBasic_elf {
				private:
					PtgElfRwV(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic_elf::Parse(buffer, max, offset); }
				public:
					static PtgElfRwV* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgElfRwV* ans = new PtgElfRwV(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgElfRwV";
					}
				};
			}
		}
	}
}