#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CRNRecord : public Record {
			public:
				CRNRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
