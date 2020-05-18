#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class RRSortRecord : public Record {
			public:
				RRSortRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
