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
					PtgArea(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					RgceArea area;
				public:
					static PtgArea* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgArea* ans = new PtgArea(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 8; }
					std::string to_string() const override {
						return "PtgArea(" + this->area.to_string() + ")";
					}
				};
			}
		}
	}
}
