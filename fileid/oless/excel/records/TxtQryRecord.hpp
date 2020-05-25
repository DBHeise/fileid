#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TxtQryRecord : public Record {
			public:
				TxtQryRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
