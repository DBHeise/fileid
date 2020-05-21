#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TxORecord : public Record, public IReParseable {
			public:
				TxORecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser * p) override {

				}
			};
		}
	}
}
