#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UsesELFsRecord : public Record {
			public:
				UsesELFsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
