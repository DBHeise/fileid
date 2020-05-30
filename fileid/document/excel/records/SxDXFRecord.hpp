#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxDXFRecord : public Record {
			public:
				SxDXFRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
