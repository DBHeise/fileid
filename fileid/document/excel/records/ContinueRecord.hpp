#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class ContinueRecord : public Record {
			public:
				ContinueRecord(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {

					Record* r = p->GetPrevRecordNotOfType(type);
					r->Data.insert(r->Data.end(), data.begin(), data.end());
					
					if (IReParseable* pr = dynamic_cast<IReParseable*>(r)) {
						pr->ReParse(p);
					}

				}

			};
		}
	}
}
