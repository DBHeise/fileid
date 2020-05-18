#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/31ed3738-e4ff-4b60-804c-ac49ac1ee6c0
			// The SupBook record specifies a supporting link and specifies the beginning of a collection of records as defined by the Globals Substream ABNF.  The collection of records specifies the contents of an external workbook, DDE data source, or OLE data source.
			class SupBookRecord : public Record {
			private:
				unsigned short ctab;
				unsigned short cch;
				std::string virtPath;
				std::string rgst;
			public:
				SupBookRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					unsigned int max = this->Data.size();
					this->ctab = common::ReadUShort(buffer, max, 0);
					this->cch = common::ReadUShort(buffer, max, 2);
				}
			};
		}
	}
}
