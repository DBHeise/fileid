#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXDIRecord : public Record {
			public:
				SXDIRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
