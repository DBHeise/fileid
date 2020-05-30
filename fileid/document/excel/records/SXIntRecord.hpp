#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXIntRecord : public Record {
			public:
				SXIntRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
