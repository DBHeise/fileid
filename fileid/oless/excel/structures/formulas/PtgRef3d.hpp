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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1ca817be-8df3-4b80-8d35-46b5eb753577
				// ptg=0x3A or 0x5A or 0x7A
				// The PtgRef3d operand specifies a reference to a single cell on one or more sheets.
				class PtgRef3d : public PtgSubType_ixti {
				private:
					
					RgceLoc loc;
				public:
					PtgRef3d(unsigned char* buffer, size_t max, unsigned int offset): PtgSubType_ixti() {
						this->Parse(buffer, max, offset); 
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType_ixti::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->loc.Parse(buffer, max, index);
						index += this->loc.bytesRead;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgRef3d(" << this->loc.to_string() << ")";
						return ss.str();
					}
				};
			}
        }
    }
}
