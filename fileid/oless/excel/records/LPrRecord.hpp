#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LPrRecord : public Record {
			public:
				LPrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
