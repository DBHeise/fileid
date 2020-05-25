#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PlotGrowthRecord : public Record {
			public:
				PlotGrowthRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
