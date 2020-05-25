#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class OleObjectSizeRecord : public Record {
			public:
				OleObjectSizeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
