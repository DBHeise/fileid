#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BookExtRecord : public Record {
			public:
				BookExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
