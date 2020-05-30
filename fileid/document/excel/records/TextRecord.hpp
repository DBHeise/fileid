#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TextRecord : public Record {
			public:
				TextRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
