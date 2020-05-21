#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CalcDeltaRecord : public Record {
			public:
				CalcDeltaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
