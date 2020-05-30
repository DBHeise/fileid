#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class FooterRecord : public Record {
			public:
				FooterRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
