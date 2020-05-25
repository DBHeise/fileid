#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DxGColRecord : public Record {
			public:
				DxGColRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
