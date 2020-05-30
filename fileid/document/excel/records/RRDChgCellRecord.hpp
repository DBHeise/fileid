#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRDChgCellRecord : public Record {
			public:
				RRDChgCellRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
