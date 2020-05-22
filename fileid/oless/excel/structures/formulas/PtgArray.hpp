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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/61167ac8-b0ca-42e5-b82c-41a25d12324c
				// ptg=0x20 or  0x40 or  0x60
				// The PtgArray operand specifies an array of values. There MUST be a PtgExtraArray in the RgbExtra corresponding to this PtgArray. The correspondence between PtgArray and PtgExtraArray structures is specified in RgbExtra.
				class PtgArray : public PtgSubType {
				private:
					PtgArray(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned char unused1;
					unsigned short unused2;
					unsigned int unused3;
				public:
					static PtgArray* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgArray* ans = new PtgArray(buffer, max, index);
						index = ans->bytesRead;

						ans->unused1 = buffer[index];
						index++;

						ans->unused2 = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->unused3 = common::ReadUInt(buffer, max, index);
						index += 4;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgArray";
					}
				};
			}
		}
	}
}