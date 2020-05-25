#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxSelectRecord : public Record {
			public:
				SxSelectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
