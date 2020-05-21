#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class EndObjectRecord : public Record {
			public:
				EndObjectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
