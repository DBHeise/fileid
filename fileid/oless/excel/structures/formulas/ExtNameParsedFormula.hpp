#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"

#include "ExtPtgRef3D.hpp"
#include "ExtPtgArea3D.hpp"
#include "ExtPtgRefErr3D.hpp"
#include "ExtPtgAreaErr3D.hpp"
#include "ExtPtgErr.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/bcdeb725-04eb-4432-ab35-0d38dd06a7cf
				// The ExtNameParsedFormula structure specifies a formula (section 2.2.2) used in an external defined name.
				class ExtNameParsedFormula : public IParseable {
				private:
					unsigned short cb;
					unsigned short extPtg;
					
					bool hasRef3d = false;
					bool hasArea3d = false;
					bool hasRefErr3d = false;
					bool hasAreaErr3d = false;
					bool hasErr = false;
					IParseable* val;

				public:
					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->cb = common::ReadUShort(buffer, max, index);
						index += 2;

						this->extPtg = buffer[index];
						index++;

						if (this->cb > 0) {
							if (this->extPtg == 0x3A) {
								//ExtPtgRef3D
								this->hasRef3d = true;
								this->val = new ExtPtgRef3D();
								
							} else if (this->extPtg == 0x3B) {
								//ExtPtgArea3D
								this->hasArea3d = true;
								this->val = new ExtPtgArea3D();

							} else if (this->extPtg == 0x3C) {
								//ExtPtgRefErr3D
								this->hasRef3d = true;
								this->val = new ExtPtgRefErr3D();

							} else if (this->extPtg == 0x3D) {
								//ExtPtgAreaErr3D
								this->hasAreaErr3d = true;
								this->val = new ExtPtgAreaErr3D();

							} else if (this->extPtg == 0x1C) {
								//ExtPtgErr
								this->hasErr = true;
								this->val = new ExtPtgErr();
							} else {
								//?
							}

							if (this->val != nullptr) {
								this->val->Parse(buffer, max, index);
								index += this->val->bytesRead;
							}
						}


						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}