#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LeftMarginRecord : public Record {
			public:
				LeftMarginRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
