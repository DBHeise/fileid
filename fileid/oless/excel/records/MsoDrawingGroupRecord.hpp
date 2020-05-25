#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MsoDrawingGroupRecord : public Record {
			public:
				MsoDrawingGroupRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
