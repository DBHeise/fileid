#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXTblRecord : public Record {
			public:
				SXTblRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
