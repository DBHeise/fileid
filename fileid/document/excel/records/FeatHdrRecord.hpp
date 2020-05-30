#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FeatHdrRecord : public Record {
			public:
				FeatHdrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
