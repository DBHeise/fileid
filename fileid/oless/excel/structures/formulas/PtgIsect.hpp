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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/477524a5-86b9-474e-8955-9ea77d659d79
				// ptg=0x0F
				// The PtgIsect structure specifies a binary-reference-operator that intersects the first expression in a binary-reference-expression with the second.
				class PtgIsect : public PtgBasic {
				private:
				public:
					PtgIsect(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { this->Parse(buffer, max, offset); }

					std::string to_string() const override {
						return "PtgIsect";
					}
				};
			}
		}
	}
}