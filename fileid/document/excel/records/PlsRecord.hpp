#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PlsRecord : public Record, public IReParseable {
			public:
				PlsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* parser) {

				}
			};
		}
	}
}
