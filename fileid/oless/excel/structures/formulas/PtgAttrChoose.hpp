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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/24fb579c-c65d-4771-94a8-4380cecdc8c8
				// ptg=0x19
				// The PtgAttrChoose structure specifies a control token.
				class PtgAttrChoose : public PtgBasic {
				private:
					PtgAttrChoose(unsigned char* buffer, size_t max, unsigned int offset) { PtgBasic::Parse(buffer, max, offset); }
					unsigned char reserved2 : 2;
					unsigned char bitChoose : 1;
					unsigned char reserved3 : 5;
					unsigned short cOffset;
					std::vector<unsigned short> rgOffset;
				public:
					static PtgAttrChoose* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						unsigned int index = offset;
						PtgAttrChoose* ans = new PtgAttrChoose(buffer, max, index);
						index += ans->bytesRead;

						ans->reserved2 = common::ExtractBits(buffer[index], 2, 1);
						ans->bitChoose = common::ExtractBits(buffer[index], 1, 3);
						ans->reserved3 = common::ExtractBits(buffer[index], 5, 4);
						index++;

						ans->cOffset = common::ReadUShort(buffer, max, index);
						index += 2;

						for (unsigned short i = 0; i < ans->cOffset; i++) { //TODO: Verify this logic???
							auto tmp = common::ReadUShort(buffer, max, index);
							index += 2;
							ans->rgOffset.push_back(tmp);
						}

						ans->bytesRead = offset - index;
						return ans;
					}
					
					std::string to_string() const override {
						return "PtgAttrChoose";
					}
				};
			}
		}
	}
}
