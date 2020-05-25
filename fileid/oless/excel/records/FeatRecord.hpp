#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FeatRecord : public Record, public IReParseable {
			public:
				FeatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
