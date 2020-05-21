#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DBQueryExtRecord : public Record {
			public:
				DBQueryExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
