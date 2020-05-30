#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRAutoFmtRecord : public Record {
			public:
				RRAutoFmtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
