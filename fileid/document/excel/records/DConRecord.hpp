#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DConRecord : public Record {
			public:
				DConRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}