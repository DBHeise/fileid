#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AxisRecord : public Record {
			public:
				AxisRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
