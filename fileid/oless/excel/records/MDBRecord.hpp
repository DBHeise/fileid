#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class MDBRecord : public Record {
			public:
				MDBRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
