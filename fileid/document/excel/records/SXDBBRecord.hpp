#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXDBBRecord : public Record {
			public:
				SXDBBRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
