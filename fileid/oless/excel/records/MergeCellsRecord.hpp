#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MergeCellsRecord : public Record {
			public:
				MergeCellsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
