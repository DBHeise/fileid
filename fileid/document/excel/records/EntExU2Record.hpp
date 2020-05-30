#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class EntExU2Record : public Record {
			public:
				EntExU2Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
