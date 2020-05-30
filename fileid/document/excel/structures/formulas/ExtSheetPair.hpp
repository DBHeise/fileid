#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/bf9eaf17-1f7b-4436-bf90-16531854f71f
				//The ExtSheetPair structure specifies a pair of sheets in the formulas of an external defined name. The sheets are in the External Workbook as specified by the preceding SupBook recor
				class ExtSheetPair : public IParseable {
				private:
					signed short itabFirst;
					signed short itabLast;
				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->itabFirst = common::ReadSShort(buffer, max, index);
						index += 2;

						this->itabLast = common::ReadSShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}