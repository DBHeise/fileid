#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SXViewLinkRecord : public Record {
			public:
				SXViewLinkRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
