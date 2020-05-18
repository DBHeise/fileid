#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			class TextPropsStreamRecord : public Record {
			public:
				TextPropsStreamRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
