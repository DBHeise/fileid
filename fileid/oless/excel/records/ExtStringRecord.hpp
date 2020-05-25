#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ExtStringRecord : public Record {
			public:
				ExtStringRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
