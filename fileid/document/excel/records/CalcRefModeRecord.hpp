#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CalcRefModeRecord : public Record {
			public:
				CalcRefModeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
