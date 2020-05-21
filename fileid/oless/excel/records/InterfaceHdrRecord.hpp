#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class InterfaceHdrRecord : public Record {
			public:
				InterfaceHdrRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
