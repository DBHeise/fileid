#pragma once

#include "../../../../common.hpp"
#include "../../MSExcel.common.hpp"
#include "../../IParsable.hpp"
#include "../../records/Record.hpp"
#include "Ptg.hpp"
#include "Rgce.hpp"
#include "RgbExtra.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// Base Class for all *ParsedFormula classes
				class ParsedFormulaBase : public IParseable {
				protected:
					unsigned short cce;
					Rgce rgce;
					IRecordParser* parser;

				public:
					ParsedFormulaBase(IRecordParser* parser) { this->parser = parser; }

					std::string ToFormulaString() {
						return this->rgce.ToTextString(this->parser);
					}

					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						this->cce = common::ReadUShort(buffer, max, index);
						index += 2;

						this->rgce.Parse(buffer, max, index);
						index += this->rgce.bytesRead;

						this->bytesRead = index - offset;
					}
				};

				class ParsedFormulaWithExtraBase : public ParsedFormulaBase {
				protected:
					RgbExtra rgcb;
				public:
					ParsedFormulaWithExtraBase(IRecordParser* parser) : ParsedFormulaBase(parser) {}

					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						ParsedFormulaBase::Parse(buffer, max, offset);

						unsigned int index = offset + this->bytesRead;

						this->rgcb.Parse(buffer, max, index);
						index += this->rgcb.bytesRead;

						this->bytesRead = index - offset;
					}

				};
			}
		}
	}
}
