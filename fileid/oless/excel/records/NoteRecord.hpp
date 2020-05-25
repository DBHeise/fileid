#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class NoteRecord : public Record {
			public:
				NoteRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
