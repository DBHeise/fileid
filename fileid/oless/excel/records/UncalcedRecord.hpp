#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UncalcedRecord : public Record {
			public:
				UncalcedRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
