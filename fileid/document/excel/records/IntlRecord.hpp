#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class IntlRecord : public Record {
			public:
				IntlRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
