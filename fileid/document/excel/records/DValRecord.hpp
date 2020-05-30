#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DValRecord : public Record {
			public:
				DValRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
