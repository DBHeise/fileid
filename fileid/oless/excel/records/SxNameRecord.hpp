#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxNameRecord : public Record {
			public:
				SxNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
