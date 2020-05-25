#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {




			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/4d6a3d1e-d7c5-405f-bbae-d01e9cb79366
			// The BOF record specifies the beginning of the individual substreams as specified by the workbook section. It also specifies history information for the substreams. 
			struct BOF8 {
				unsigned short vers;
				unsigned short dt;
				unsigned short rubBuild;
				unsigned short rupYear;
				unsigned short fWin : 1;
				unsigned short fRisc : 1;
				unsigned short fBeta : 1;
				unsigned short fWinAny : 1;
				unsigned short fMacAny : 1;
				unsigned short fBetaAny : 1;
				unsigned short unused1 : 2;
				unsigned short fRiscAny : 1;
				unsigned short fOOM : 1;
				unsigned short fGIJmp : 1;
				unsigned short unused2 : 2;
				unsigned short fFontLimit : 1;
				unsigned short verXLHigh : 1;
				unsigned short unused3 : 1;
				unsigned short reserved1 : 13;
				unsigned short verLowestBiff : 8;
				unsigned short verLastXLSaved : 4;
				unsigned long reserved2 : 20;
			};

			struct BOF2 {
				unsigned short vers;
				unsigned short type;
			};

			struct BOF34 {
				unsigned short vers;
				unsigned short type;
				unsigned short unused;
			};
			struct BOF5 {
				unsigned short vers;
				unsigned short type;
				unsigned short build;
				unsigned short year;
			};

			std::string GetBOFType(unsigned int type) {
				switch (type)
				{
				case 0x0005: return "Globals";
				case 0x0006: return "VB Module";
				case 0x0010: return "Sheet";
				case 0x0020: return "Chart";
				case 0x0040: return "Macro";
				case 0x0100: return "Workspace";
				default: return "Unknown";
				}
			}


			class BOFRecord : public Record {
			private:
				BOF8* bof = nullptr;
			public:
				BOFRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{					
					this->bof = (BOF8*)this->Data.data();
				}

				BOF8* GetRawBOF() {
					return this->bof;
				}

				std::string ToXml() const override
				{					
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();

					str << "<Version>" << this->bof->vers << "</Version>";
					str << "<DocumentType>" << this->bof->dt << "</DocumentType>";
					str << "<DocumentTypeStr>" << GetBOFType(this->bof->dt) << "</DocumentTypeStr>";
					str << "<RUPBuild>" << this->bof->rubBuild << "</RUPBuild>";
					str << "<RUPYear>" << this->bof->rupYear << "</RUPYear>";

					str << "<LastEditWindows>" << this->bof->fWin << "</LastEditWindows>";
					str << "<LastEditRisc>" << this->bof->fRisc << "</LastEditRisc>";
					str << "<LastEditBeta>" << this->bof->fBeta << "</LastEditBeta>";
					str << "<AnyEditWindows>" << this->bof->fWinAny << "</AnyEditWindows>";
					str << "<AnyEditRisc>" << this->bof->fRiscAny << "</AnyEditRisc>";
					str << "<AnyEditMac>" << this->bof->fMacAny << "</AnyEditMac>";
					str << "<AnyEditBeta>" << this->bof->fBetaAny << "</AnyEditBeta>";
					
					str << "<FailureOutOfMemory>" << this->bof->fOOM << "</FailureOutOfMemory>";
					str << "<FailureOutOfMemoryRender>" << this->bof->fGIJmp << "</FailureOutOfMemoryRender>";

					str << "<FontLimitHit>" << this->bof->fFontLimit << "</FontLimitHit>";
					
					str << "<HighestXLVersion>" << this->bof->verXLHigh << "</HighestXLVersion>";
					str << "<LowestBiff>" << this->bof->verLowestBiff << "</LowestBiff>";
					str << "<LastSavedXLVersion>" << this->bof->verLastXLSaved << "</LastSavedXLVersion>";

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson() << ",";

					str << "\"Version\":" << this->bof->vers << ",";
					str << "\"DocumentType\":" << this->bof->dt << ",";
					str << "\"DocumentTypeStr\":\"" << GetBOFType(this->bof->dt) << "\",";
					str << "\"RUPBuild\":" << this->bof->rubBuild << ",";
					str << "\"RUPYear\":" << this->bof->rupYear << ",";

					str << "\"LastEditWindows\":" << this->bof->fWin << ",";
					str << "\"LastEditRisc\":" << this->bof->fRisc << ",";
					str << "\"LastEditBeta\":" << this->bof->fBeta << ",";
					str << "\"AnyEditWindows\":" << this->bof->fWinAny << ",";
					str << "\"AnyEditRisc\":" << this->bof->fRiscAny << ",";
					str << "\"AnyEditMac\":" << this->bof->fMacAny << ",";
					str << "\"AnyEditBeta\":" << this->bof->fBetaAny << ",";

					str << "\"FailureOutOfMemory\":" << this->bof->fOOM << ",";
					str << "\"FailureOutOfMemoryRender\":" << this->bof->fGIJmp << ",";

					str << "\"FontLimitHit\":" << this->bof->fFontLimit << ",";

					str << "\"HighestXLVersion\":" << this->bof->verXLHigh << ",";
					str << "\"LowestBiff\":" << this->bof->verLowestBiff << ",";
					str << "\"LastSavedXLVersion\":" << this->bof->verLastXLSaved;

					str << "}";
					return str.str();
				}
			};
		}
	}
}