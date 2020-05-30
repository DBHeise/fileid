#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/40e69183-2cd3-4051-87ba-2f3ccb82bcfa
				// ptg=0x1F
				// The PtgNum operand specifies a floating-point value.
				class PtgNum : public PtgBasic {
				private:
					double value;
				public:
					PtgNum(unsigned char* buffer, size_t max, unsigned int offset): value(0.0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						this->value = ReadXNumFromBytes(&buffer[offset + 1]);
						this->bytesRead += 8;
					}

					std::string to_string() const override {
						return "PtgNum(" + std::to_string(this->value) + ")";
					}
				};
			}
		}
	}
}
