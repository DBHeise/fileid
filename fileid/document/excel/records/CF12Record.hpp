#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CF12Record : public Record {
			public:
				CF12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
