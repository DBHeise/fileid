#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class HideObjRecord : public Record {
			public:
				HideObjRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
