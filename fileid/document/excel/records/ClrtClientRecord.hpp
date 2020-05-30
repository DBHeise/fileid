#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ClrtClientRecord : public Record {
			public:
				ClrtClientRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
