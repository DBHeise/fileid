#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AutoFilterInfoRecord : public Record {
			public:
				AutoFilterInfoRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
