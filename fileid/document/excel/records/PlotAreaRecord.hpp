#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PlotAreaRecord : public Record {
			public:
				PlotAreaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
