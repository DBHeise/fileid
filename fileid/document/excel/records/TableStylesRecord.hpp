#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TableStylesRecord : public Record {
			public:
				TableStylesRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
