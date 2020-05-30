#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXStringRecord : public Record {
			public:
				SXStringRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
