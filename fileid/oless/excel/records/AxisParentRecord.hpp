#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AxisParentRecord : public Record {
			public:
				AxisParentRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
