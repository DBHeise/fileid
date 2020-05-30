#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DataLabExtRecord : public Record {
			public:
				DataLabExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
