#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DConRefRecord : public Record {
			public:
				DConRefRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
