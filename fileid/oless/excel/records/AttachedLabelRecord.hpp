#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AttachedLabelRecord : public Record {
			public:
				AttachedLabelRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
