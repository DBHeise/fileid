#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Chart3dRecord : public Record {
			public:
				Chart3dRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
