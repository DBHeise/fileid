#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class HFPictureRecord : public Record {
			public:
				HFPictureRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
