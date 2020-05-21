#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class HeaderRecord : public Record {
			public:
				HeaderRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
