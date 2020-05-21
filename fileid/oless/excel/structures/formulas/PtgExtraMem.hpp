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

				//// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/0a225048-f0a1-4093-8b0b-6d8f8497f8ce
				//class PtgExtraMem : public IParseable {
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