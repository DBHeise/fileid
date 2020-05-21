#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RealTimeDataRecord : public Record {
			public:
				RealTimeDataRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
