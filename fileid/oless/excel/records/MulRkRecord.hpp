#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MulRkRecord : public Record {
			public:
				MulRkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
