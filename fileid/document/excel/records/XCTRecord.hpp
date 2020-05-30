#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class XCTRecord : public Record {
			public:
				XCTRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
