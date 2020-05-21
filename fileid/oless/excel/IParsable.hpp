#pragma once

namespace oless {
	namespace excel {

			class IParseable {

			public:
				unsigned int bytesRead;
				virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) = 0;
			};
	}
}