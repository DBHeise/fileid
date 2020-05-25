#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ExternSheetRecord : public Record {
			public:
				ExternSheetRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
