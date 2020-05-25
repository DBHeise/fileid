#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ContinueFrt11Record : public Record {
			public:
				ContinueFrt11Record(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
