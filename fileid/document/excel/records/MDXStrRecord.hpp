#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MDXStrRecord : public Record {
			public:
				MDXStrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
