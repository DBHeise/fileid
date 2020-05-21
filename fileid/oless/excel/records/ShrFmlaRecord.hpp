#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ShrFmlaRecord : public Record {
			public:
				ShrFmlaRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
