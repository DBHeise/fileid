#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TickRecord : public Record {
			public:
				TickRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
