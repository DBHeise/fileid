#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PrintSizeRecord : public Record {
			public:
				PrintSizeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
