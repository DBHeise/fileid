#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DefaultTextRecord : public Record {
			public:
				DefaultTextRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
