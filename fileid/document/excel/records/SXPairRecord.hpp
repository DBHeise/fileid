#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXPairRecord : public Record {
			public:
				SXPairRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
