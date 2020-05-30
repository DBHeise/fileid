#pragma once

#include "Record.hpp"
#include "../structures/FormatRun.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AlRunsRecord : public Record {
			private:
				unsigned short cRuns;
				std::vector<FormatRun*> rgRuns;
			public:
				AlRunsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->cRuns = common::ReadUShort(buffer, max, index);
					index += 2;

					for (unsigned short i = 0; i < this->cRuns; i++) {
						auto fr = new FormatRun();
						fr->Parse(buffer, max, index);
						index += fr->bytesRead;
						this->rgRuns.push_back(fr);
					}
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << "}";
					return str.str();
				}

			};
		}
	}
}
