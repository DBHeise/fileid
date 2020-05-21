#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class NumberRecord : public Record {
			public:
				NumberRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
