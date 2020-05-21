#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRDInfoRecord : public Record {
			public:
				RRDInfoRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
