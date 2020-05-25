#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXVDExRecord : public Record {
			public:
				SXVDExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
