#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXPIRecord : public Record {
			public:
				SXPIRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
