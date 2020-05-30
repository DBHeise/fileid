#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UsrChkRecord : public Record {
			public:
				UsrChkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
