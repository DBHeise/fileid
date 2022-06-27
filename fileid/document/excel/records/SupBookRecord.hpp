#pragma once

#include "Record.hpp"
#include "../structures/XLUnicodeString.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/31ed3738-e4ff-4b60-804c-ac49ac1ee6c0
			// The SupBook record specifies a supporting link and specifies the beginning of a collection of records as defined by the Globals Substream ABNF.  The collection of records specifies the contents of an external workbook, DDE data source, or OLE data source.
			class SupBookRecord : public Record {				
			public:
				unsigned short ctab;
				unsigned short cch;
				bool HasVirtPath = false;
				std::string virtPath;
				std::vector<std::string> rgst;				

				SupBookRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->ctab = common::ReadUShort(buffer, max, index);
					index += 2;

					this->cch = common::ReadUShort(buffer, max, index);
					index += 2;

					if (index < max) {
						if (this->cch >= 0x01 && this->cch <= 0xFF) {
							this->HasVirtPath = true;
							this->virtPath = common::ReadString(buffer, max, index, this->cch);
							index += this->cch;
						}
					}
					if (index < max) {
						if (this->cch == 0x3A01 || this->cch == 0x0401) {
							for (unsigned int i = 0; i < this->ctab; i++) {
								auto s = oless::excel::structures::XLUnicodeString::Read(buffer, index, max);
								index += s.bytesRead;
								rgst.push_back(s.string);
							}
						}
					}
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<ctab>" << this->ctab << "</ctab>";
					str << "<cch>" << this->cch << "</cch>";
					if (this->HasVirtPath) {
						str << "<virtPath>" << this->virtPath << "</virtPath>";
					}
					if (this->rgst.size() > 0) {
						str << "<rgst>";
						for (auto it = this->rgst.begin(); it < this->rgst.end(); it++) {
							str << "<string>" << (*it) << "</string>";
						}
						str << "</rgst>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"ctab\":" << this->ctab;
					str << ",\"cch\":" << this->cch;
					if (this->HasVirtPath) {
						str << ",\"virtPath\":\"" << this->virtPath << "\"";
					}
					if (this->rgst.size() > 0) {
						str << ",\"rgst\":[" << common::vector_join(this->rgst, ",", true) << "]";
					}
					
					str << "}";
					return str.str();
				}
			};
		}
	}
}
