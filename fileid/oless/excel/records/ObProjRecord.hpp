#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ObProjRecord : public Record {
			public:
				ObProjRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
