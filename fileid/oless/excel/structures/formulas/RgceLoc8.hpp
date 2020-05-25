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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/32ce1ec2-e11b-428c-ba62-d835613968e1
				// ptg=
				// The RgceLoc8 structure  specifies a single cell reference.
				class RgceLoc8 {
				public:
					RgceLoc rgceLoc;
					unsigned int reserved;
					void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
						this->rgceLoc.Parse(buffer, offset, max);
						this->reserved = common::ReadUInt(buffer, max, offset + 4, true);
					}
				};
			}
		}
	}
}