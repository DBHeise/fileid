#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CatLabRecord : public Record {
			public:
				CatLabRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
