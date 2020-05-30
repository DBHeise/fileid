#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXDBExRecord : public Record {
			public:
				SXDBExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
