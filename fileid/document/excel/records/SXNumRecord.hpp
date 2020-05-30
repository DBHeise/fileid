#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXNumRecord : public Record {
			public:
				SXNumRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
