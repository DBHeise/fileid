#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SerAuxErrBarRecord : public Record {
			public:
				SerAuxErrBarRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
