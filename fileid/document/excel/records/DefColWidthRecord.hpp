#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DefColWidthRecord : public Record {
			public:
				DefColWidthRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
