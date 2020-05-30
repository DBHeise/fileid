#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class Feature12Record : public Record, public IReParseable {
			public:
				Feature12Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

				}

				virtual void ReParse(IRecordParser* p) override {

				}
			};
		}
	}
}
