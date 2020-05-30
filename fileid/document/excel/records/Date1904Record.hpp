#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Date1904Record : public Record {
			public:
				Date1904Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
