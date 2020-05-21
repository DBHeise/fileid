#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SyncRecord : public Record {
			public:
				SyncRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
