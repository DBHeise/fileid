#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MDXTupleRecord : public Record {
			public:
				MDXTupleRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
