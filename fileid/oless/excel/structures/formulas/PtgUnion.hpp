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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/90d54742-4776-4271-a08c-39bd73b7b8fc
				// ptg=0x10
				// The PtgUnion structure specifies a binary-reference-operator that specifies a union of the first expression in a binary-reference-expression with the second.
				class PtgUnion : public PtgBasic {
				private:
					PtgUnion(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
				public:
					static PtgUnion* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgUnion* ans = new PtgUnion(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgUnion";
					}
				};
			}
        }
    }
}
