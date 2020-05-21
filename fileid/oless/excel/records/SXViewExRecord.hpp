#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXViewExRecord : public Record {
			public:
				SXViewExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
