#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DefaultRowHeightRecord : public Record {
			public:
				DefaultRowHeightRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
