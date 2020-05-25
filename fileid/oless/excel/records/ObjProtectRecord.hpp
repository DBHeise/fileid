#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ObjProtectRecord : public Record {
			public:
				ObjProtectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
