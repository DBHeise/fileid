#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXViewEx9Record : public Record {
			public:
				SXViewEx9Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
