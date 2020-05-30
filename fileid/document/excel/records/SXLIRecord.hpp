#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXLIRecord : public Record {
			public:
				SXLIRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
