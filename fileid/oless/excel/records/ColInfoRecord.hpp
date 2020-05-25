#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ColInfoRecord : public Record {
			public:
				ColInfoRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
