#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FilterModeRecord : public Record {
			public:
				FilterModeRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
