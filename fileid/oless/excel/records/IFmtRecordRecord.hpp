#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class IFmtRecordRecord : public Record {
			public:
				IFmtRecordRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
