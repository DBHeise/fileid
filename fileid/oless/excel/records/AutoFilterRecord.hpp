#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AutoFilterRecord : public Record {
			public:
				AutoFilterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
