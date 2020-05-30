#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ProtectRecord : public Record {
			public:
				ProtectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
