#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AreaRecord : public Record {
			public:
				AreaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
