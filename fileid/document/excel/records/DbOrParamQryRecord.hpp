#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DbOrParamQryRecord : public Record {
			public:
				DbOrParamQryRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
