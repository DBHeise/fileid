#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class TemplateRecord : public Record {
			public:
				TemplateRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
