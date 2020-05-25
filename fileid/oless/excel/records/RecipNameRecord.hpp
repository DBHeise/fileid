#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RecipNameRecord : public Record {
			public:
				RecipNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
