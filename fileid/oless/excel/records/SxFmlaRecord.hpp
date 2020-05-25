#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxFmlaRecord : public Record {
			public:
				SxFmlaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
