#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class InterfaceEndRecord : public Record {
			public:
				InterfaceEndRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
