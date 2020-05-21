#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PieRecord : public Record {
			public:
				PieRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
