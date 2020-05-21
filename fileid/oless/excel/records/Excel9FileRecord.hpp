#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Excel9FileRecord : public Record {
			public:
				Excel9FileRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
