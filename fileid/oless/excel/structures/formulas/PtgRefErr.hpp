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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d86972da-19ea-4a6e-a71d-49129e930521
				// ptg=0x2A or 0x4A or 0x6A
				// The PtgRefErr operand specifies an invalid reference to a cell.
				class PtgRefErr : public PtgSubType {
				private:
					PtgRefErr(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned short unused1;
					unsigned short unused2;
				public:
					static PtgRefErr* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgRefErr* ans = new PtgRefErr(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 4; }
					std::string to_string() const override {
						return "PtgRefErr";
					}
				};
			}
		}
    }
}
