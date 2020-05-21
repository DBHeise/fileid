#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXRngRecord : public Record {
			public:
				SXRngRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
