#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DBCellRecord : public Record {
			public:
				DBCellRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
