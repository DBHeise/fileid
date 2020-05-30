#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DConNameRecord : public Record {
			public:
				DConNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
