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

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/2b3c0de0-14c8-436a-ae32-477c2a075c60
				// ptg=0x27 or 0x47 or 0x67
				// The PtgMemErr mem token specifies that the result of a binary-reference-expression in a mem-area-expression is an error code.
				class PtgMemErr : public PtgSubType {
				private:
					PtgMemErr(unsigned char* buffer, size_t max, unsigned int offset) { PtgSubType::Parse(buffer, max, offset); }
					BErr err;
					unsigned char unused1;
					unsigned short unused2;
					unsigned short cce;
				public:
					static PtgMemErr* Parse(unsigned char* buffer, size_t max, unsigned int offset) {
						PtgMemErr* ans = new PtgMemErr(buffer, max, offset);
						return ans;
					}
					unsigned int size() const override { return PtgSubType::size() + 6; }
					std::string to_string() const override {
						return "PtgMemErr";
					}
				};
			}
		}
	}
}
