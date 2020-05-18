#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {


			struct ExternNameHeader {
				unsigned char fBuiltin : 1;
				unsigned char fWantAdvise : 1;
				unsigned char fWantPict : 1;
				unsigned char fOle : 1;
				unsigned char fOleLink : 1;
				unsigned short cf : 10;
				unsigned char fIcon : 1;
			};

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/95495582-1465-4bdd-8183-b16f8e8eaf74
			// The ExternName record specifies an external defined name, a User Defined Function (UDF) reference on a XLL or COM add-in, a DDE data item or an OLE data item, depending on the value of the virtPath field in the preceding SupBook record.
			class ExternNameRecord : public Record {
			private:
				ExternNameHeader* header;
			public:
				ExternNameRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					this->header = reinterpret_cast<ExternNameHeader*>(buffer);
				}
			};
		}
	}
}
