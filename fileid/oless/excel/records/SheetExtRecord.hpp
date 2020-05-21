#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SheetExtRecord : public Record {
			public:
				SheetExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
