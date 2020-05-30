#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class DropDownObjIdsRecord : public Record {
			public:
				DropDownObjIdsRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
