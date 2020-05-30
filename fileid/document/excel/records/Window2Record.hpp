#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Window2Record : public Record {
			public:
				Window2Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
