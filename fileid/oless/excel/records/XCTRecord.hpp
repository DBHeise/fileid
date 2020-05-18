#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class XCTRecord : public Record {
			public:
				XCTRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
