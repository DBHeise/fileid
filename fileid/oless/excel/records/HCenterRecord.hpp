#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class HCenterRecord : public Record {
			public:
				HCenterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
