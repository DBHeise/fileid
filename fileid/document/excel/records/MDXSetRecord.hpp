#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MDXSetRecord : public Record {
			public:
				MDXSetRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
