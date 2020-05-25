#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class IndexRecord : public Record {
			public:
				IndexRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
