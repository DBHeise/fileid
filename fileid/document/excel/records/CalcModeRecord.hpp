#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CalcModeRecord : public Record {
			public:
				CalcModeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
