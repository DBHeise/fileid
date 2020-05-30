#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MsoDrawingRecord : public Record, public IReParseable {
			public:
				MsoDrawingRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
