#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CbUsrRecord : public Record {
			public:
				CbUsrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
