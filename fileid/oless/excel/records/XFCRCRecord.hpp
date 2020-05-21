#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class XFCRCRecord : public Record {
			public:
				XFCRCRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
