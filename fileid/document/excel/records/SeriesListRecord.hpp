#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SeriesListRecord : public Record {
			public:
				SeriesListRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
