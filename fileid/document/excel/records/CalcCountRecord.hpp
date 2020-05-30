#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CalcCountRecord : public Record {
			public:
				CalcCountRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
