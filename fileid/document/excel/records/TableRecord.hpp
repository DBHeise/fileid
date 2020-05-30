#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TableRecord : public Record {
			public:
				TableRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
