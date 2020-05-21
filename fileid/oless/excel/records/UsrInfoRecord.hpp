#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UsrInfoRecord : public Record {
			public:
				UsrInfoRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
