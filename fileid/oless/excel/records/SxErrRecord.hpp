#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxErrRecord : public Record {
			public:
				SxErrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
