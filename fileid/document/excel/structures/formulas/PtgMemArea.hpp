#pragma once

#include "../../../../common.hpp"

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
					unsigned int unused;
					unsigned short cce;
				public:
					PtgMemArea(unsigned char* buffer, size_t max, unsigned int offset): unused(0), cce(0), PtgSubType() { 
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
						return "PtgMemArea";
					}
				};
			}
		}
	}
}