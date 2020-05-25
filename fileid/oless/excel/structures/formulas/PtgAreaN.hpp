#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceAreaRel.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f2c8529a-25b1-4c75-838b-a48ef6384f86
				// ptg=0x2D or 0x4D or 0x6D
				// The PtgAreaN operand specifies a reference to a rectangular range of cells as an RgceAreaRel.
				class PtgAreaN : public PtgSubType {
				private:					
					RgceAreaRel area;
				public:
					PtgAreaN(unsigned char* buffer, size_t max, unsigned int offset): PtgSubType() {
						this->Parse(buffer,max,offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->area.Parse(buffer, max, offset + 1);
						this->bytesRead += this->area.bytesRead;
					}

					std::string to_string() const override {
						return "PtgAreaN";
					}
				};
			}
		}
	}
}