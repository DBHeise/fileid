#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRTabIdRecord : public Record {
			public:
				RRTabIdRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
