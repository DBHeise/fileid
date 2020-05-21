#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LineRecord : public Record {
			public:
				LineRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
