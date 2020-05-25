#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PasswordRecord : public Record {
			public:
				PasswordRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
