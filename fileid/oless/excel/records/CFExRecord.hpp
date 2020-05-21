#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CFExRecord : public Record {
			public:
				CFExRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
