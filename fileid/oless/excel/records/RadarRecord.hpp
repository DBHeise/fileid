#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RadarRecord : public Record {
			public:
				RadarRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
