#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PLVRecord : public Record {
			public:
				PLVRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
