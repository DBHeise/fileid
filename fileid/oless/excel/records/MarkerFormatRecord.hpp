#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MarkerFormatRecord : public Record {
			public:
				MarkerFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
