#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FrameRecord : public Record {
			public:
				FrameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
