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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5b2a3be1-7d98-4632-ac94-671c44d442c7
				// ptg=0x02
				// The PtgTbl structure specifies that the Rgce that contains this PtgTbl is part of a data table (1) or an ObjectParsedFormula.
				class PtgTbl : public PtgBasic {
				private:
					PtgTbl(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned short row;
					unsigned short col;
				public:
					static PtgTbl* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgTbl* ans = new PtgTbl(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 4; }
					std::string to_string() const override {
						return "PtgTbl";
					}
				};
			}
        }
    }
}
