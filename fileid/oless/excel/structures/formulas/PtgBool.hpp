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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/d59e28db-4d6f-4c86-bcc9-c8a783e352ec
				// ptg=0x1D
				// The PtgBool operand specifies a Boolean value.
				class PtgBool : public PtgBasic {
				private:
					
					unsigned char boolean;
				public:
					PtgBool(unsigned char* buffer, size_t max, unsigned int offset) : boolean(0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						this->boolean = buffer[offset + 1];
						this->bytesRead++;
					}
					
					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgBool(";
						ss << std::boolalpha << (bool)this->boolean;
						ss << ")";
						return ss.str();
					}
				};
			}
		}
	}
}