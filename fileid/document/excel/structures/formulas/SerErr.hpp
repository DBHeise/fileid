#pragma once

#include "SerAr.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/153fddfb-8c8a-4d6d-9e51-d0940244e5b4
				// The SerErr structure specifies an error value in an array of values.
				class SerErr : public SerAr {
				public:
					unsigned char reserved1; //0x10
					unsigned char err;
					unsigned char reserved2;
					unsigned short unused1;
					unsigned int unused2;
				};
			}
		}
	}
}
