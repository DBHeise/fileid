#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PaletteRecord : public Record {
			public:
				PaletteRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
