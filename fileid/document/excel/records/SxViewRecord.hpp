#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxViewRecord : public Record {
			public:
				SxViewRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
