#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SerParentRecord : public Record {
			public:
				SerParentRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
