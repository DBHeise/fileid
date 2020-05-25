#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FontXRecord : public Record {
			public:
				FontXRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
