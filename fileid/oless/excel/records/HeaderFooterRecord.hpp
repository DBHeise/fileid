#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class HeaderFooterRecord : public Record {
			public:
				HeaderFooterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
