#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class EndBlockRecord : public Record {
			public:
				EndBlockRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
