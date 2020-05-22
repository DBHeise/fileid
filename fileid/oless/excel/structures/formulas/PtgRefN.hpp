#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceLocRel.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/bf3b872b-ba11-4489-a94a-e3937f1bb032
				// ptg=0x2C or 0x4C or 0x6C
				// The PtgRefN operand specifies a reference to a single cell as an RgceLocRel.
				class PtgRefN : public PtgSubType {
				private:
					PtgRefN(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					RgceLocRel loc;
				public:
					static PtgRefN* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgRefN* ans = new PtgRefN(buffer, max, index);
						index += ans->bytesRead;

						ans->loc.Parse(buffer, max, index);
						index += ans->loc.bytesRead;

						ans->bytesRead = index - offset;
						return ans;
					}
					std::string to_string() const override {
						return "PtgRefN";
					}
				};
			}
		}
    }
}
