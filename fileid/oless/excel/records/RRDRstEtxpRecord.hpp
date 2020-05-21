#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RRDRstEtxpRecord : public Record {
			public:
				RRDRstEtxpRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
