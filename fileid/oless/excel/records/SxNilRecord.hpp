#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxNilRecord : public Record {
			public:
				SxNilRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
