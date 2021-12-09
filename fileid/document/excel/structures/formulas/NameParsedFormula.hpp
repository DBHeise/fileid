#pragma once

#include "../../../../common.hpp"
#include "../../IParsable.hpp"
#include "../../records/Record.hpp"
#include "Rgce.hpp"
#include "RgbExtra.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9afd1c6c-c486-4d9c-b644-3708428d2ffb
				// The NameParsedFormula structure specifies a formula (section 2.2.2) used in a defined name.
				class NameParsedFormula : public IParseable, public common::IMiniExportable {
				private:
					Rgce rgce;
					RgbExtra rgcb;

					IRecordParser* parser;

				public:
					NameParsedFormula(IRecordParser* parser)
					{
						this->parser = parser;
					}
					virtual void Parse2(unsigned char* buffer, unsigned int rgceSize, std::size_t max, unsigned int offset) {
						unsigned int index = offset;

						this->rgce.Parse(buffer, index + rgceSize, index);
						index += this->rgce.bytesRead;

						this->rgcb.Parse(buffer, max, index);
						index += this->rgcb.bytesRead;

						this->bytesRead = max - offset;
					}

					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						this->bytesRead = max - offset;
					}
					virtual std::string ToXml() const override {
						std::ostringstream str;
						str << "<NameParsedFormula>";
						str << "</NameParsedFormula>";
						return str.str();
					}
					virtual std::string ToJson() const override {
						std::ostringstream str;
						str << "{";
						str << "}";
						return str.str();
					}
				};
			}
		}
	}
}