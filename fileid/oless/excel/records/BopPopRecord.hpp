#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BopPopRecord : public Record {
			public:
				BopPopRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
