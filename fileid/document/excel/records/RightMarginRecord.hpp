#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RightMarginRecord : public Record {
			public:
				RightMarginRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
