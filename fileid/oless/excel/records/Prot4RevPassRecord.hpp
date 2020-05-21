#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Prot4RevPassRecord : public Record {
			public:
				Prot4RevPassRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
