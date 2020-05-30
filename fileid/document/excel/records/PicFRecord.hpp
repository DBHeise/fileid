#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class PicFRecord : public Record {
			public:
				PicFRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
