#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UserSViewBeginRecord : public Record {
			public:
				UserSViewBeginRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
