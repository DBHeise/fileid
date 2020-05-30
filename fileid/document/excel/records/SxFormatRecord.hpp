#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxFormatRecord : public Record {
			public:
				SxFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
