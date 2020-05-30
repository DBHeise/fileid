#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MTRSettingsRecord : public Record {
			public:
				MTRSettingsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
