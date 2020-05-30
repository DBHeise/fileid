#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class StartBlockRecord : public Record {
			public:
				StartBlockRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
