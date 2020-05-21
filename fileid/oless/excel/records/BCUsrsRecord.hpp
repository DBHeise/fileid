#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BCUsrsRecord : public Record {
			public:
				BCUsrsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
