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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f9aa266f-f1e9-4341-a232-e9f7ec94b8f1
				// ptg=0x01
				// The PtgExp structure specifies that the containing Rgce is part of an array formula (section 2.2.2) or shared formula and specifies the row and column of the cell in which that formula exists.
				class PtgExp : public PtgBasic {
				private:
					unsigned short row;
					unsigned short col;
				public:
					PtgExp(unsigned char* buffer, size_t max, unsigned int offset): row(0), col(0), PtgBasic() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->row = common::ReadUShort(buffer, max, index);
						index += 2;

						this->col = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}
					
					std::string to_string() const override {
						std::ostringstream ss;
						ss << "PtgExp(" << ColNumToName(this->col + 1) << this->row + 1 << ")";
						return ss.str();
					}
				};
			}
		}
	}
}
