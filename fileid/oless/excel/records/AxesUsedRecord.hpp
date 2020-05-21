#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AxesUsedRecord : public Record {
			public:
				AxesUsedRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
