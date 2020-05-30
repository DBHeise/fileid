#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LineFormatRecord : public Record {
			public:
				LineFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
