#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CrtLayout12ARecord : public Record {
			public:
				CrtLayout12ARecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
