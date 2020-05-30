#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PrintGridRecord : public Record {
			public:
				PrintGridRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
