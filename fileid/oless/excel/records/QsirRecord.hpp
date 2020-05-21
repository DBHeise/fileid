#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class QsirRecord : public Record {
			public:
				QsirRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
