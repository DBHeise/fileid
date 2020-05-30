#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class VCenterRecord : public Record {
			public:
				VCenterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
