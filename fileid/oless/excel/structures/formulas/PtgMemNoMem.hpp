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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/dfa39d4c-b7cb-4bf7-b5e8-015b84fd6e48
				// ptg=0x28 or 0x48 or 0x68
				// The PtgMemNoMem mem token specifies that the result of the binary-reference-expression in a mem-area-expression failed to cache.
				class PtgMemNoMem : public PtgSubType {
				private:
					
					unsigned int unused;
					unsigned short cce;
				public:
					PtgMemNoMem(unsigned char* buffer, size_t max, unsigned int offset): unused(0), cce(0), PtgSubType() { 
						this->Parse(buffer, max, offset); 
					}
					
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->unused = common::ReadUInt(buffer, max, index);
						index += 4;

						this->cce = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgMemNoMem";
					}
				};
			}
		}
	}
}