#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PieFormatRecord : public Record {
			public:
				PieFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
