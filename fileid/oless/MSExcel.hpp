#pragma once

#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"


namespace OleStructuredStorage {
	namespace Excel {
		struct BOF {
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
			unsigned short verLowestBiff : 4;
			unsigned long reserved2 : 20;
		};

		struct BoundSheetHeader {
			unsigned int lbPlyPos;
			unsigned short hsState : 2;
			unsigned short unused1 : 6;
			unsigned short dt : 8;
		};
		struct ShortXLUnicodeStringHeader {
			unsigned short cch : 8;
			unsigned short fHighByte : 1;
			unsigned short reserved1 : 7;
		};

		struct XLUnicodeStringHeader {
			unsigned short cch;
			unsigned short fHighByte : 1;
			unsigned short reserved1 : 7;
		};

		unsigned int read2ByteInt(unsigned char* block, int offset) {
			int ans = 0;
			ans = ((int)block[offset + 1] << 8) | ((int)block[offset]);
			return ans;
		}

		std::string readXLUnicodeString(unsigned char* block, int offset) {
			int index = offset;
			XLUnicodeStringHeader* header = reinterpret_cast<XLUnicodeStringHeader*>(block + index);
			int byteCount = 0;
			if (header->fHighByte == 0x0) {
				byteCount = header->cch;
			}
			else {
				byteCount = header->cch * 2;
			}
			index += 3;

			std::string name(reinterpret_cast<char const*>(block + index), byteCount);
			return name;
		}

		std::string readShortXLUnicodeString(unsigned char* block, int offset) {
			int index = offset;
			ShortXLUnicodeStringHeader* header = reinterpret_cast<ShortXLUnicodeStringHeader*>(block + index);
			unsigned int byteCount = 0;
			if (header->fHighByte == 0x0) {
				byteCount = header->cch;
			}
			else {
				byteCount = header->cch * 2;
			}
			index += 2;

			std::string name(reinterpret_cast<char const*>(block + index), byteCount);
			return name;
		}

		std::string GetVersion_Excel(unsigned short version) {
			std::string ans;

			switch (version) {
			case 1280: ans = "BIFF5"; break;
			case 1536: ans = "BIFF8"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}

		std::string GetVisibilityStr(unsigned short visibility) {
			std::string ans;
			switch (visibility) {
			case 0x00: ans = "Visible"; break;
			case 0x01: ans = "Hidden"; break;
			case 0x02: ans = "Very Hidden"; break;
			default: ans = "Unknown/Undocumented visiblitiy"; break;
			}
			return ans;
		}
		std::string GetSheetTypeStr(unsigned short type) {
			std::string ans;
			switch (type) {
			case 0x00: ans = "Worksheet or Dialog sheet"; break;
			case 0x01: ans = "Macro sheet"; break;
			case 0x02: ans = "Chart sheet"; break;
			case 0x06: ans = "VBA Module"; break;
			default: ans = "Unknown/Undocumented type"; break;
			}
			return ans;
		}

		struct SheetInfo {			
			std::string		Name;
			unsigned short	Visiblity;
			unsigned short  Type;
		};

		class ExcelExtensionInfo : public common::ExtensionInfo {
		private:
			//Global Stream
			//Substream vectors
			std::vector<SheetInfo> sheets;
		public:
			ExcelExtensionInfo() : common::ExtensionInfo() {
				this->Extension = "xls";
				this->Name = "Microsoft Office Excel Workbook";
			}
			void ParseStream(POLE::Stream* workbookStream) {
				
				//TODO: ??more efficient way of reading the stream instead of pulling in the entire body-chunk...
				POLE::uint64 streamSize = workbookStream->size();
				unsigned char* buffer = new unsigned char[streamSize];
				//TODO: memset_s(buffer, 0, streamSize ??
				POLE::uint64 bytesRead = workbookStream->read(buffer, streamSize);
				if (bytesRead > streamSize) {
					throw std::runtime_error("bytesRead > streamSize...how is this even possible!");
				}
				else if (bytesRead < streamSize) {
					//?? what do ??
				}

				int index = 0;
				bool isNextRecordBOF = true;

				while (index < streamSize)
				{
					if (isNextRecordBOF) {
						Excel::BOF* bof = reinterpret_cast<Excel::BOF*>(buffer + index);
						index += 20;
						isNextRecordBOF = false;
						if (index == 0) { //Global BOF
							this->Version = bof->rubBuild;
							this->VersionName = GetVersion_Excel(this->Version);
							this->SubType = this->VersionName;
						}
						else { //SubStream BOF

						}
					}
					else {
						unsigned int recordType = read2ByteInt(buffer, index);
						index += 2;
						unsigned int recordSize = read2ByteInt(buffer, index);
						index += 2;

						switch (recordType) {
						case 0x0085: { //Bound Sheet
							BoundSheetHeader* header = reinterpret_cast<BoundSheetHeader*>(buffer + index);							
							SheetInfo si;
							si.Name = readShortXLUnicodeString(buffer, index+6);
							si.Type = header->dt;
							si.Visiblity = header->hsState;
							this->sheets.push_back(si);
							break;
						}
						case 0x01BA: { //CodeName
							//std::string name = readXLUnicodeString(buffer, index);
							//std::cout << name << std::endl;
							break;
						}
						case 0x0A:
							isNextRecordBOF = true;
							break;
						}
						index += recordSize;
					}
				}

				delete buffer;

			}

			virtual std::string ToJson() {
				std::ostringstream str;
				str << "{ \"extension\" : \"" << this->Extension << "\"";
				if (this->Name.size() > 0) {
					str << ", \"name\":\"" << this->Name << "\"";
				}
				if (this->SubType.size() > 0) {
					str << ", \"subtype\":\"" << common::JsonEscape(this->SubType) << "\"";
				}
				if (this->Version > 0) {
					str << ", \"version\" : \"" << this->Version << "\"";
				}
				if (this->VersionName.size() > 0) {
					str << ", \"versionname\" : \"" << this->VersionName << "\"";
				}
				if (this->sheets.size() > 0) {
					str << ", \"Sheets\": [";
					for (std::vector<SheetInfo>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {
						if (i != this->sheets.begin()) str << ",";
						str << "{";
						str << "\"Name\":\"" << common::JsonEscape((*i).Name) << "\"";
						str << ",\"Visiblity\":\"" << GetVisibilityStr((*i).Visiblity) << "\"";
						str << ",\"Type\":\"" << GetSheetTypeStr((*i).Type) << "\"";
						str << "}";
					}
					str << "]";
				}

				str << "}";
				return str.str();
			}
			virtual std::string ToXml() {
				std::ostringstream str;
				str << "<item>";
				str << "<extension>" << this->Extension << "</extension>";
				if (this->Name.size() > 0) {
					str << "<name>" << this->Name << "</name>";
				}
				if (this->SubType.size() > 0) {
					str << "<subtype>" << this->SubType << "</subtype>";
				}
				if (this->Version > 0) {
					str << "<version>" << this->Version << "</version>";
				}
				if (this->VersionName.size() > 0) {
					str << "<versionname>" << this->VersionName << "</versionname>";
				}
				if (this->sheets.size() > 0) {
					str << "<sheets>";
					for (std::vector<SheetInfo>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {						
						str << "<sheet>";
						str << "<name>" << (*i).Name << "</name>";
						str << "<visiblity>" << GetVisibilityStr((*i).Visiblity) << "</visiblity>";
						str << "<type>" << GetSheetTypeStr((*i).Type) << "</type>";
						str << "</sheet>";
					}
					str << "</sheets>";
				}
				str << "</item>";
				return str.str();
			}
		};
	}
}
