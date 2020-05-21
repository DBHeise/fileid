#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BackupRecord : public Record {
			public:
				BackupRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
