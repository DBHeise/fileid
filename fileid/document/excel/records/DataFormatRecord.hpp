#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DataFormatRecord : public Record {
			public:
				DataFormatRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
