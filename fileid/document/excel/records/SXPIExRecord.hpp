#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXPIExRecord : public Record {
			public:
				SXPIExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
