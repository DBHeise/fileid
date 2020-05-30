#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LegendExceptionRecord : public Record {
			public:
				LegendExceptionRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
