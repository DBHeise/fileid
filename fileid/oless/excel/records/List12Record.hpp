#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class List12Record : public Record {
			public:
				List12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
