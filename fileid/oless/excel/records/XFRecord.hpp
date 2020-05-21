#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class XFRecord : public Record {
			public:
				XFRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
