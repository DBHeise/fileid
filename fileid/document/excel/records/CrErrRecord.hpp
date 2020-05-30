#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CrErrRecord : public Record {
			public:
				CrErrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
