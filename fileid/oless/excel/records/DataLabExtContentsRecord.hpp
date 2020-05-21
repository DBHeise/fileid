#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DataLabExtContentsRecord : public Record {
			public:
				DataLabExtContentsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
