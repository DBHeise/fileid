#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FontRecord : public Record {
			public:
				FontRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
