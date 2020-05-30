#pragma once

#include "../../../../common.hpp"

#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "Ptg.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/42e28815-da53-45ba-80f2-2a68ddbbfcf9
				// ptg=0x18
				// The PtgElfRwV natural language formula operand specifies a value class reference to a range within a row which is represented by a single-cell natural language label.
				class PtgElfRwV : public PtgBasic_elf {
				private:
					RgceElfLoc loc;
				public:
					PtgElfRwV(unsigned char* buffer, size_t max, unsigned int offset) : PtgBasic_elf() {
						this->Parse(buffer, max, offset);
					}
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgBasic_elf::Parse(buffer, max, offset);
						unsigned int index = offset + this->bytesRead;

						this->loc.Parse(buffer, max, index);
						index += this->loc.bytesRead;

						this->bytesRead = index - offset;
					}
					std::string to_string() const override {
						return "PtgElfRwV";
					}
				};
			}
		}
	}
}