#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BRAIRecord : public Record {
			public:
				BRAIRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
