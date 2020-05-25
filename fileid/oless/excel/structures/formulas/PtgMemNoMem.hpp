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
					PtgMemNoMem(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned int unused;
					unsigned short cce;
				public:
					static PtgMemNoMem* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgMemNoMem* ans = new PtgMemNoMem(buffer, max, index);
						index += ans->bytesRead;

						ans->unused = common::ReadUInt(buffer, max, index);
						index += 4;

						ans->cce = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgMemNoMem";
					}
				};
			}
		}
	}
}