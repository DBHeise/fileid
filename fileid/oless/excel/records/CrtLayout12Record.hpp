#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CrtLayout12Record : public Record {
			public:
				CrtLayout12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
