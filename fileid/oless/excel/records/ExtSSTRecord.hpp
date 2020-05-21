#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ExtSSTRecord : public Record {
			public:
				ExtSSTRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
