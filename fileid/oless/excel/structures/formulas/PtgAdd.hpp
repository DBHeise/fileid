#pragma once

#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/27db2f45-11e8-4238-94ed-92fd9c5721fb
				// ptg=0x03
				// The PtgAdd structure specifies a binary-value-operator that adds the second expression in a binary-value-expression to the first.
				class PtgAdd : public PtgBasic {
				private:
					PtgAdd(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
				public:
					static PtgAdd* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgAdd* ans = new PtgAdd(buffer, max, offset);
						return ans;
					}
					std::string to_string() const override {
						return "PtgAdd";
					}
				};

			}
		}
	}
}