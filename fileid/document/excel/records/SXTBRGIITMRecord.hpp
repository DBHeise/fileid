#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXTBRGIITMRecord : public Record {
			public:
				SXTBRGIITMRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
