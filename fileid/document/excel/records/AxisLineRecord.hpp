#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AxisLineRecord : public Record {
			public:
				AxisLineRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
