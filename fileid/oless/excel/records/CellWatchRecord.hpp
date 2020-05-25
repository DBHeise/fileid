#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CellWatchRecord : public Record {
			public:
				CellWatchRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
