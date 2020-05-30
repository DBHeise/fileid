#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BookBoolRecord : public Record {
			public:
				BookBoolRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
