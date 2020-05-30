#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AxcExtRecord : public Record {
			public:
				AxcExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
