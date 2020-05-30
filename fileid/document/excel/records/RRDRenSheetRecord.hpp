#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRDRenSheetRecord : public Record {
			public:
				RRDRenSheetRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
