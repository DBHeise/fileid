#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRInsertShRecord : public Record {
			public:
				RRInsertShRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
