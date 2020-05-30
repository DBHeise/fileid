#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRFormatRecord : public Record {
			public:
				RRFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
