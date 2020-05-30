#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CalcIterRecord : public Record {
			public:
				CalcIterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
