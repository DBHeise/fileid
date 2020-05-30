#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DocRouteRecord : public Record {
			public:
				DocRouteRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
