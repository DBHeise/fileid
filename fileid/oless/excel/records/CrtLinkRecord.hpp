#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CrtLinkRecord : public Record {
			public:
				CrtLinkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
