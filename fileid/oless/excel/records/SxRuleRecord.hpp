#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxRuleRecord : public Record {
			public:
				SxRuleRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
