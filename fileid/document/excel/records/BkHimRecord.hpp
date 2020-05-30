#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BkHimRecord : public Record, public IReParseable {
			public:
				BkHimRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
