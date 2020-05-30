#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FeatHdr11Record : public Record {
			public:
				FeatHdr11Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
