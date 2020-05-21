#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxTbpgRecord : public Record {
			public:
				SxTbpgRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
