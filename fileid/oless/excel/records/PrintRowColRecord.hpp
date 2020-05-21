#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PrintRowColRecord : public Record {
			public:
				PrintRowColRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
