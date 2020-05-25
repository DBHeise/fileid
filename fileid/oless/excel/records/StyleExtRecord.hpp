#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class StyleExtRecord : public Record {
			public:
				StyleExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
