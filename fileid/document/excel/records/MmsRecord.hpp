#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MmsRecord : public Record {
			public:
				MmsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
