#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TextPropsStreamRecord : public Record {
			public:
				TextPropsStreamRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
