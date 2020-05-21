#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TopMarginRecord : public Record {
			public:
				TopMarginRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
