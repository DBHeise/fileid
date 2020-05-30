#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class WOptRecord : public Record {
			public:
				WOptRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
