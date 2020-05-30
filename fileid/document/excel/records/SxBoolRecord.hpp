#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxBoolRecord : public Record {
			public:
				SxBoolRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
