#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXVDTExRecord : public Record {
			public:
				SXVDTExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
