#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FileSharingRecord : public Record {
			public:
				FileSharingRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
