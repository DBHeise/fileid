#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LegendRecord : public Record {
			public:
				LegendRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
