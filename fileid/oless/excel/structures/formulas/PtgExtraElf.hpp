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

				//// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/a40d14cc-51ea-4e59-bdc3-eb1abb1ad1ef
				//class PtgExtraElf : public IParseable {
				//public:
				//	virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
				//		unsigned int index = offset;

				//		this->bytesRead = index - offset;
				//	}
				//};
			}
		}
	}
}