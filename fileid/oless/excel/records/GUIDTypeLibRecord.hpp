#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class GUIDTypeLibRecord : public Record {
			public:
				GUIDTypeLibRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
