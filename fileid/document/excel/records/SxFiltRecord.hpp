#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class SxFiltRecord : public Record {
			public:
				SxFiltRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
