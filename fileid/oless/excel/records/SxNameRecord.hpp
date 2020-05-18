#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class SxNameRecord : public Record {
			public:
				SxNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
