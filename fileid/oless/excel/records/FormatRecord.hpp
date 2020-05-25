#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FormatRecord : public Record {
			public:
				FormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
