#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXFDBTypeRecord : public Record {
			public:
				SXFDBTypeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
