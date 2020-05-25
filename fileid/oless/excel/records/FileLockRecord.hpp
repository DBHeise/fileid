#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FileLockRecord : public Record {
			public:
				FileLockRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
