#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ObNoMacrosRecord : public Record {
			public:
				ObNoMacrosRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
