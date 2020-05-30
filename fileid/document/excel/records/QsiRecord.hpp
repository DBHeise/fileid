#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class QsiRecord : public Record {
			public:
				QsiRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
