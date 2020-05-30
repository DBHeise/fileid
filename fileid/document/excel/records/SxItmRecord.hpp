#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxItmRecord : public Record, public IReParseable {
			public:
				SxItmRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
