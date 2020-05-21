#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DvRecord : public Record {
			public:
				DvRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
