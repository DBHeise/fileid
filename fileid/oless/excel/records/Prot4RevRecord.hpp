#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Prot4RevRecord : public Record {
			public:
				Prot4RevRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
