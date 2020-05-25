#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ChartFormatRecord : public Record {
			public:
				ChartFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
