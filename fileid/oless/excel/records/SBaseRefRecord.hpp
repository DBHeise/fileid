#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SBaseRefRecord : public Record {
			public:
				SBaseRefRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
