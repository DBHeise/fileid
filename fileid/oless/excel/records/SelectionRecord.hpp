#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SelectionRecord : public Record {
			public:
				SelectionRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
