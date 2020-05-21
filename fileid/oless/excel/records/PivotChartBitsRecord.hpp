#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PivotChartBitsRecord : public Record {
			public:
				PivotChartBitsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
