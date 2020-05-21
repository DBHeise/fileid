#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class CompressPicturesRecord : public Record {
			public:
				CompressPicturesRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
