#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CatSerRangeRecord : public Record {
			public:
				CatSerRangeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
