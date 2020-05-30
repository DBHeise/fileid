#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ArrayRecord : public Record {
			public:
				ArrayRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
