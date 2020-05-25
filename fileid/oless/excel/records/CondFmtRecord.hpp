#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CondFmtRecord : public Record {
			public:
				CondFmtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
