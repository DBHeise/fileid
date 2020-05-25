#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ScenarioProtectRecord : public Record {
			public:
				ScenarioProtectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
