#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FrtFontListRecord : public Record {
			public:
				FrtFontListRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
