#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SurfRecord : public Record {
			public:
				SurfRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
