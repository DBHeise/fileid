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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/078f34be-35cc-4abc-960b-34f48d4da6ee
				// ptg=0x26 or 0x46 or 0x66
				// The PtgMemArea mem token specifies that the result of a binary-reference-expression in a mem-area-expression is a range of cells. The RgbExtra corresponding to this structure MUST contain a PtgExtraMem that specifies the range of cells.
				class PtgMemArea : public PtgSubType {
				private:
					PtgMemArea(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					unsigned int unused;
					unsigned short cce;
				public:
					static PtgMemArea* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgMemArea* ans = new PtgMemArea(buffer, max, index);
						index += ans->bytesRead;

						ans->unused = common::ReadUInt(buffer, max, index);
						index += 4;

						ans->cce = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->bytesRead = index - offset;
						return ans;
					}

					std::string to_string() const override {
						return "PtgMemArea";
					}
				};
			}
		}
	}
}