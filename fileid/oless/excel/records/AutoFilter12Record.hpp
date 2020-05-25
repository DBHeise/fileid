#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AutoFilter12Record : public Record, public IReParseable {
			public:
				AutoFilter12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
				
				virtual void ReParse(IRecordParser* p) override {

				}

			};
		}
	}
}
