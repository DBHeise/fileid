#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "../../records/ExternNameRecord.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f9eba5de-1ff6-4d52-9753-f9c1e446c774
				// ptg=0x39 or 0x59 or 0x79
				// The PtgNameX structure specifies a reference to a defined name in an external workbook.
				class PtgNameX : public PtgSubType_ixti {
				private:
					std::string name;
				public:
					unsigned int nameindex;
					
					PtgNameX(unsigned char* buffer, size_t max, unsigned int offset) : nameindex(0), PtgSubType_ixti() {
						this->Parse(buffer, max, offset); 
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType_ixti::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->nameindex = common::ReadUInt(buffer, max, index, true);
						index += 4;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgNameX(" + std::to_string(this->nameindex) + ")";
					}
				};
			}
        }
    }
}
