#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ForceFullCalculationRecord : public Record {
			public:
				ForceFullCalculationRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
