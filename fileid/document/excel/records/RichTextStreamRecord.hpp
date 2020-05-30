#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RichTextStreamRecord : public Record {
			public:
				RichTextStreamRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
