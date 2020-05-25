#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8d791d7b-82f2-4259-9230-ea58afe5fd07
			// The existence of the WriteProtect record specifies that the file is write-protected.
			class WriteProtectRecord : public Record {
			public:
				WriteProtectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}
			};
		}
	}
}
