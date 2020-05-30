#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ScenManRecord : public Record {
			public:
				ScenManRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
