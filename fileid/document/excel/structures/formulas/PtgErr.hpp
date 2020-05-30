#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "BErr.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/4746c46e-8301-4d72-aaa8-742f5404b5db
				// ptg=0x1C
				// The PtgErr operand specifies an error code.
				class PtgErr : public PtgBasic {
				private:
					
					BErr err;
				public:
					PtgErr(unsigned char* buffer, size_t max, unsigned int offset): PtgBasic() { 
						this->Parse(buffer, max, offset);
					}
					
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						this->err = (BErr)buffer[offset + 1];
						this->bytesRead++;
					}
					
					std::string to_string() const override {
						return "PtgErr('" + ErrorValueString(this->err) + "')";
					}
				};
			}
		}
	}
}