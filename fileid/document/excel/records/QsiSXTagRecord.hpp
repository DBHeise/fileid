#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class QsiSXTagRecord : public Record {
			public:
				QsiSXTagRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
