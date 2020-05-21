#pragma once

#include "Record.hpp"
#include "../structures/formulas/NameParsedFormula.hpp"
#include "../structures/XLUnicodeStringNoCch.hpp"

namespace oless {
	namespace excel {
		namespace records {

			struct fakeLblHeader {
				unsigned short fHidden : 1;
				unsigned short fFunc : 1;
				unsigned short fOB : 1;
				unsigned short fProc : 1;
				unsigned short fCalcExp : 1;
				unsigned short fBuiltin : 1;
				unsigned short fGrp : 6;
				unsigned short reserved1 : 1;
				unsigned short fPublished : 1;
				unsigned short fWorkbookParam : 1;

				unsigned char chKey;
				unsigned char cch;
				unsigned short cce;
				unsigned short reserved3;
				unsigned short itab;
				unsigned char reserved4;
				unsigned char reserved5;
				unsigned char reserved6;
				unsigned char reserved7;
			};

			class LblRecord : public Record {
			private:
				fakeLblHeader* header;
				std::string name;
				excel::structures::formulas::NameParsedFormula rgce;

			public:
				LblRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->header = reinterpret_cast<fakeLblHeader*>(buffer + index);
					index += 14;

					auto tmpName = excel::structures::XLUnicodeStringNoCch::Read(buffer, max, index, this->header->cch);
					this->name = tmpName.string;
					index += tmpName.bytesRead;

					this->rgce.Parse(buffer, max, index);
					index += this->rgce.bytesRead;
				}

				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<fHidden>" << this->header->fHidden << "</fHidden>";
					str << "<fFunc>" << this->header->fFunc << "</fFunc>";
					str << "<fOB>" << this->header->fOB << "</fOB>";
					str << "<fProc>" << this->header->fProc << "</fProc>";
					str << "<fCalcExp>" << this->header->fCalcExp << "</fCalcExp>";
					str << "<fBuiltin>" << this->header->fBuiltin << "</fBuiltin>";
					str << "<fGrp>" << this->header->fGrp << "</fGrp>";
					str << "<reserved1>" << this->header->reserved1 << "</reserved1>";
					str << "<fPublished>" << this->header->fPublished << "</fPublished>";
					str << "<fWorkbookParam>" << this->header->fWorkbookParam << "</fWorkbookParam>";
					str << "<chKey>" << (unsigned short)this->header->chKey << "</chKey>";
					str << "<cch>" << (unsigned short)this->header->cch << "</cch>";
					str << "<cce>" << this->header->cce << "</cce>";
					str << "<reserved3>" << this->header->reserved3 << "</reserved3>";
					str << "<itab>" << this->header->itab << "</itab>";
					str << "<reserved4>" << (unsigned short)this->header->reserved4 << "</reserved4>";
					str << "<reserved5>" << (unsigned short)this->header->reserved5 << "</reserved5>";
					str << "<reserved6>" << (unsigned short)this->header->reserved6 << "</reserved6>";
					str << "<reserved7>" << (unsigned short)this->header->reserved7 << "</reserved7>";
					str << "<name>" << common::XmlEscape(this->name) << "</name>";
					str << this->rgce.ToXml();
					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"fHidden\":" << this->header->fHidden;
					str << ",\"fFunc\":" << this->header->fFunc;
					str << ",\"fOB\":" << this->header->fOB;
					str << ",\"fProc\":" << this->header->fProc;
					str << ",\"fCalcExp\":" << this->header->fCalcExp;
					str << ",\"fBuiltin\":" << this->header->fBuiltin;
					str << ",\"fGrp\":" << this->header->fGrp;
					str << ",\"reserved1\":" << this->header->reserved1;
					str << ",\"fPublished\":" << this->header->fPublished;
					str << ",\"fWorkbookParam\":" << this->header->fWorkbookParam;
					str << ",\"chKey\":" << (unsigned short)this->header->chKey;
					str << ",\"cch\":" << (unsigned short)this->header->cch;
					str << ",\"cce\":" << this->header->cce;
					str << ",\"reserved3\":" << this->header->reserved3;
					str << ",\"itab\":" << this->header->itab;
					str << ",\"reserved4\":" << (unsigned short)this->header->reserved4;
					str << ",\"reserved5\":" << (unsigned short)this->header->reserved5;
					str << ",\"reserved6\":" << (unsigned short)this->header->reserved6;
					str << ",\"reserved7\":" << (unsigned short)this->header->reserved7;
					str << ",\"name\":\"" << common::JsonEscape(this->name) << "\"";
					str << ",\"namedparsedformula\":" << this->rgce.ToJson();
					str << "}";
					return str.str();
				}
			};
		}
	}
}
