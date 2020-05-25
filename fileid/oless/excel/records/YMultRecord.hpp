#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class YMultRecord : public Record {
			public:
				YMultRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
