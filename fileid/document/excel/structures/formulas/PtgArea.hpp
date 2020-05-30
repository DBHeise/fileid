#pragma once

#include "../../IParsable.hpp"
#include "Ptg.hpp"
#include "RgceArea.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {				

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/b3c714c2-4fcf-4888-9e15-1cbf17e4d5d3
				// ptg=0x25 or 0x45 or 0x65
				// The PtgArea operand specifies a reference to a rectangular range of cells.
				class PtgArea : public PtgSubType {
				private:					
					RgceArea area;
				public:
					PtgArea(unsigned char* buffer, size_t max, unsigned int offset):PtgSubType() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->area.Parse(buffer, max, offset);
						this->bytesRead += this->area.bytesRead;
					}

					std::string to_string() const override {
						return "PtgArea(" + this->area.to_string() + ")";
					}
				};
			}
		}
	}
}
