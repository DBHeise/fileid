#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class GutsRecord : public Record {
			public:
				GutsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
