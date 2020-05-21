#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class UserSViewBegin_ChartRecord : public Record {
			public:
				UserSViewBegin_ChartRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
