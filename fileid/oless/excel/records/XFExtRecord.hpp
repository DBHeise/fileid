#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class XFExtRecord : public Record {
			public:
				XFExtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
