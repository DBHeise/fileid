#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CUsrRecord : public Record {
			public:
				CUsrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
