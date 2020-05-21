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
					PtgExp(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned short row;
					unsigned short col;
				public:
					static PtgExp* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgExp* ans = new PtgExp(buffer, max, offset);
						ans->row = common::ReadUShort(buffer, max, offset + 1);
						ans->col = common::ReadUShort(buffer, max, offset + 3);
						return ans;
					}
					unsigned int size() const override { return PtgBasic::size() + 4; }
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
