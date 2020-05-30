#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CondFmt12Record : public Record {
			public:
				CondFmt12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
