#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class NameCmtRecord : public Record {
			public:
				NameCmtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
