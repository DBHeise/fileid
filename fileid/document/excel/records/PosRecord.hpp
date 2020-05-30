#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PosRecord : public Record {
			public:
				PosRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
