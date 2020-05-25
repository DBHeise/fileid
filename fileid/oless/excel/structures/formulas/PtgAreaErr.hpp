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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/bbc29b52-b581-4417-b18c-a4ac430a8dc0
				// ptg=0x2B or 0x4B or 0x6B
				// The PtgAreaErr operand specifies an invalid reference to a cell range.
				class PtgAreaErr : public PtgSubType {
				private:
					
					unsigned short unused1;
					unsigned short unused2;
					unsigned short unused3;
					unsigned short unused4;
				public:
					PtgAreaErr(unsigned char* buffer, size_t max, unsigned int offset) : unused1(0), unused2(0), unused3(0), unused4(0), PtgSubType() {
						this->Parse(buffer, max, offset);						
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->unused1 = common::ReadUShort(buffer, max, index);
						index += 2;

						this->unused2 = common::ReadUShort(buffer, max, index);
						index += 2;

						this->unused3 = common::ReadUShort(buffer, max, index);
						index += 2;

						this->unused4 = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}
										
					std::string to_string() const override {
						return "PtgAreaErr";
					}
				};
			}
		}
	}
}