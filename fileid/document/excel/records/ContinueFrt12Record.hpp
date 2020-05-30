#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ContinueFrt12Record : public Record {
			public:
				ContinueFrt12Record(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
