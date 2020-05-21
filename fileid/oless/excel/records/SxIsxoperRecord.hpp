#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxIsxoperRecord : public Record {
			public:
				SxIsxoperRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
