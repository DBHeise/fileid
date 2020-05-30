#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UnitsRecord : public Record {
			public:
				UnitsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
