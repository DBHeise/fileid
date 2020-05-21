#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class QsifRecord : public Record {
			public:
				QsifRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
