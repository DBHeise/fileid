#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SerFmtRecord : public Record {
			public:
				SerFmtRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
