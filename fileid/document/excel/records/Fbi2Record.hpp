#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Fbi2Record : public Record {
			public:
				Fbi2Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
