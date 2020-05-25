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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/350feab7-1a62-4668-8052-d58c880a3fd2
				// ptg=0x13
				// The PtgUminus structure specifies a unary-operator which generates the additive inverse of a unary-expression.
				class PtgUminus : public PtgBasic {
				private:
					PtgUminus(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
				public:
					static PtgUminus* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgUminus* ans = new PtgUminus(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgUminus";
					}
				};
			}
        }
    }
}
