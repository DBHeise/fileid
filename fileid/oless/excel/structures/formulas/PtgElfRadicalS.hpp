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


				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e3112a89-f771-4043-82a9-18b3d4c1e137
				// ptg=0x18
				// The PtgElfRadicalS natural language formula operand specifies a reference class reference to a range which is represented by a multiple-cell natural language label. The range is specified by the PtgArea or PtgAreaErr record which follows this PtgElfRadicalS in the formula (section 2.2.2). There MUST be a PtgExtraElf in the RgbExtra corresponding to this PtgElfRadicalS. The correspondence between PtgElfRadicalS and PtgExtraElf structures is specified in RgbExtra.
				class PtgElfRadicalS : public PtgBasic_elf {
				private:
					unsigned int unused;
				public:
					PtgElfRadicalS(unsigned char* buffer, size_t max, unsigned int offset): unused(0), PtgBasic_elf() { 
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic_elf::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->unused = common::ReadUInt(buffer, max, offset);
						index += 4;

						this->bytesRead = index - offset;
					}

					std::string to_string() const override {
						return "PtgElfRadicalS";
					}
				};
			}
		}
	}
}