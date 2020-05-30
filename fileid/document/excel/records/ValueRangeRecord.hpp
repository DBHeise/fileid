#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ValueRangeRecord : public Record {
			public:
				ValueRangeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
