#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ObjRecord : public Record, public IReParseable {
			public:
				ObjRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
