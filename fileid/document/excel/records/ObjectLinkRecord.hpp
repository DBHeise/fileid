#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ObjectLinkRecord : public Record {
			public:
				ObjectLinkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
