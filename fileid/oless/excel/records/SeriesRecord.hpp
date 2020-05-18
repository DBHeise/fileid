#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class SeriesRecord : public Record {
			public:
				SeriesRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
