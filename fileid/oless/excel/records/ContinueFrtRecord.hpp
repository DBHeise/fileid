#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ContinueFrtRecord : public Record {
			public:
				ContinueFrtRecord(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
