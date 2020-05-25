#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class VerticalPageBreaksRecord : public Record {
			public:
				VerticalPageBreaksRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
