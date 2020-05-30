#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UsrExclRecord : public Record {
			public:
				UsrExclRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
