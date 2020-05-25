#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "RgceLoc.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fc7c380b-d793-4219-a897-e47e13c4e055
				// ptg=0x24 or 0x44 or 0x64
				// The PtgRef operand specifies a reference to a single cell as an RgceLoc.
				class PtgRef : public PtgSubType {
				private:
					RgceLoc loc;
				public:
					PtgRef(unsigned char* buffer, size_t max, unsigned int offset): PtgSubType() {
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
						return "PtgRef(" + this->loc.to_string() + ")";
					}
				};
			}
        }
    }
}
