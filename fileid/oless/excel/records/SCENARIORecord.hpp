#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SCENARIORecord : public Record {
			public:
				SCENARIORecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
