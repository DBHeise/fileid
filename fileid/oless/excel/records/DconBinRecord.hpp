#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DconBinRecord : public Record {
			public:
				DconBinRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
