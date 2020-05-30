#pragma once

#include "../../../../common.hpp"

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
					RgceLocRel loc;
				public:
					PtgRefN(unsigned char* buffer, size_t max, unsigned int offset): PtgSubType() { 
						this->Parse(buffer, max, offset);
					}

					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->loc.Parse(buffer, max, index);
						index += this->loc.bytesRead;

						this->bytesRead = index - offset;
					}
					std::string to_string() const override {
						return "PtgRefN";
					}
				};
			}
		}
    }
}
