#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Compat12Record : public Record {
			public:
				Compat12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
