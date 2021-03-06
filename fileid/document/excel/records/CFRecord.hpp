#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CFRecord : public Record {
			public:
				CFRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
