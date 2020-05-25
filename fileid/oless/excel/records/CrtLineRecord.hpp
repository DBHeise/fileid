#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CrtLineRecord : public Record {
			public:
				CrtLineRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
