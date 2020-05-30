#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/5f05c166-dfe3-4bbf-85aa-31c09c0258c0
				// ptg=0x23 or 0x43 or 0x63
				// The PtgName operand specifies a reference to a defined name in the same workbook as the containing Rgce.
				class PtgName : public PtgSubType {
				private:
				public:
					unsigned int nameindex;

					PtgName(unsigned char* buffer, size_t max, unsigned int offset): nameindex(0), PtgSubType() {
						this->Parse(buffer, max, offset);
					}

					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->nameindex = common::ReadUInt(buffer, max, index, true);
						index += 4;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgName(" + std::to_string(this->nameindex) + ")";
					}
				};
			}
        }
    }
}
