#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FrtWrapperRecord : public Record {
			public:
				FrtWrapperRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
