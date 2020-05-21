#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXExRecord : public Record {
			public:
				SXExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
