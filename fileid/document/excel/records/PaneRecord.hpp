#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PaneRecord : public Record {
			public:
				PaneRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
