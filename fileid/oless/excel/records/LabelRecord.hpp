#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class LabelRecord : public Record {
			public:
				LabelRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
