#pragma once

#include "Record.hpp"
#include "SupBookRecord.hpp"
#include "../structures/ShortXLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class AddinUdf {
			private:
				unsigned int reserved;
				AddinUdf() {}
			public: 
				std::string udfName;

				static AddinUdf Read(const unsigned char* buffer, std::size_t max, const unsigned int offset) {
					AddinUdf ans;
					unsigned int index = offset;

					ans.reserved = common::ReadUInt(buffer, max, index, true);
					index += 4;
					
					auto s = excel::structures::ShortXLUnicodeString::Read(buffer, index);
					ans.udfName = s.string;

					return ans;
				}
			};

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

				bool hasAddinUdf = false;
				std::string addinUdf;
			public:
				ExternNameRecord(IRecordParser* p, unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->header = reinterpret_cast<ExternNameHeader*>(buffer);
					index += 2;

					auto last = p->GetPrevRecordOfType(0x01AE);

					if (SupBookRecord* sb = dynamic_cast<SupBookRecord*>(last)) {

						if (sb->cch == 0x3A01) {
							auto body = AddinUdf::Read(buffer, max, index);
							this->hasAddinUdf = true;
							this->addinUdf = body.udfName;
						} else {
							if (this->header->fOle) {
								//ExternDdeLinkNoOpr
							}
							else if (this->header->fOleLink) {
								//ExternOleDdeLink
							}
							else {
								//ExternDocName
							}
						}
					}
				
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<fBuiltin>" << this->header->fBuiltin << "</fBuiltin>";
					str << "<fWantAdvise>" << this->header->fWantAdvise << "</fWantAdvise>";
					str << "<fWantPict>" << this->header->fWantPict << "</fWantPict>";
					str << "<fOle>" << this->header->fOle << "</fOle>";
					str << "<fOleLink>" << this->header->fOleLink << "</fOleLink>";
					str << "<cf>" << this->header->cf << "</cf>";
					str << "<fIcon>" << this->header->fBuiltin << "</fIcon>";
					if (this->hasAddinUdf) {
						str << "<addinUdf>" << this->addinUdf << "</addinUdf>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"fBuiltin\":" << (unsigned short)this->header->fBuiltin;
					str << ",\"fWantAdvise\":" << (unsigned short)this->header->fWantAdvise;
					str << ",\"fWantPict\":" << (unsigned short)this->header->fWantPict;
					str << ",\"fOle\":" << (unsigned short)this->header->fOle;
					str << ",\"fOleLink\":" << (unsigned short)this->header->fOleLink;
					str << ",\"cf\":" << (unsigned short)this->header->cf;
					str << ",\"fIcon\":" << (unsigned short)this->header->fBuiltin;
					if (this->hasAddinUdf) {
						str << ",\"addinUdf\":\"" << this->addinUdf << "\"";
					}
					str << "}";
					return str.str();
				}

			};
		}
	}
}
