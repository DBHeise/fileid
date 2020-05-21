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
					PtgBool(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char boolean;
				public:
					static PtgBool* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgBool* ans = new PtgBool(buffer, max, offset);
						ans->boolean = buffer[offset + 1];
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 1; }
					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgBool(";
						ss << std::boolalpha << this->boolean;
						ss << ")";
						return ss.str();
					}
				};
			}
		}
	}
}