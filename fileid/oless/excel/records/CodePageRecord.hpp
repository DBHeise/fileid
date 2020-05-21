#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
			std::string CPToString(unsigned short cp) {
				std::string ans;
				switch (cp) {
				case 37: ans = "IBM EBCDIC US-Canada"; break;
				case 437: ans = "OEM United States"; break;
				case 500: ans = "IBM EBCDIC International"; break;
				case 708: ans = "Arabic (ASMO 708)"; break;
				case 709: ans = "Arabic (ASMO-449+, BCON V4)"; break;
				case 710: ans = "Arabic - Transparent Arabic"; break;
				case 720: ans = "Arabic (Transparent ASMO); Arabic (DOS)"; break;
				case 737: ans = "OEM Greek (formerly 437G); Greek (DOS)"; break;
				case 775: ans = "OEM Baltic; Baltic (DOS)"; break;
				case 850: ans = "OEM Multilingual Latin 1; Western European (DOS)"; break;
				case 852: ans = "OEM Latin 2; Central European (DOS)"; break;
				case 855: ans = "OEM Cyrillic (primarily Russian)"; break;
				case 857: ans = "OEM Turkish; Turkish (DOS)"; break;
				case 858: ans = "OEM Multilingual Latin 1 + Euro symbol"; break;
				case 860: ans = "OEM Portuguese; Portuguese (DOS)"; break;
				case 861: ans = "OEM Icelandic; Icelandic (DOS)"; break;
				case 862: ans = "OEM Hebrew; Hebrew (DOS)"; break;
				case 863: ans = "OEM French Canadian; French Canadian (DOS)"; break;
				case 864: ans = "OEM Arabic; Arabic (864)"; break;
				case 865: ans = "OEM Nordic; Nordic (DOS)"; break;
				case 866: ans = "OEM Russian; Cyrillic (DOS)"; break;
				case 869: ans = "OEM Modern Greek; Greek, Modern (DOS)"; break;
				case 870: ans = "IBM EBCDIC Multilingual/ROECE (Latin 2); IBM EBCDIC Multilingual Latin 2"; break;
				case 874: ans = "ANSI/OEM Thai (ISO 8859-11); Thai (Windows)"; break;
				case 875: ans = "IBM EBCDIC Greek Modern"; break;
				case 932: ans = "ANSI/OEM Japanese; Japanese (Shift-JIS)"; break;
				case 936: ans = "ANSI/OEM Simplified Chinese (PRC, Singapore); Chinese Simplified (GB2312)"; break;
				case 949: ans = "ANSI/OEM Korean (Unified Hangul Code)"; break;
				case 950: ans = "ANSI/OEM Traditional Chinese (Taiwan; Hong Kong SAR, PRC); Chinese Traditional (Big5)"; break;
				case 1026: ans = "IBM EBCDIC Turkish (Latin 5)"; break;
				case 1047: ans = "IBM EBCDIC Latin 1/Open System"; break;
				case 1140: ans = "IBM EBCDIC US-Canada (037 + Euro symbol); IBM EBCDIC (US-Canada-Euro)"; break;
				case 1141: ans = "IBM EBCDIC Germany (20273 + Euro symbol); IBM EBCDIC (Germany-Euro)"; break;
				case 1142: ans = "IBM EBCDIC Denmark-Norway (20277 + Euro symbol); IBM EBCDIC (Denmark-Norway-Euro)"; break;
				case 1143: ans = "IBM EBCDIC Finland-Sweden (20278 + Euro symbol); IBM EBCDIC (Finland-Sweden-Euro)"; break;
				case 1144: ans = "IBM EBCDIC Italy (20280 + Euro symbol); IBM EBCDIC (Italy-Euro)"; break;
				case 1145: ans = "IBM EBCDIC Latin America-Spain (20284 + Euro symbol); IBM EBCDIC (Spain-Euro)"; break;
				case 1146: ans = "IBM EBCDIC United Kingdom (20285 + Euro symbol); IBM EBCDIC (UK-Euro)"; break;
				case 1147: ans = "IBM EBCDIC France (20297 + Euro symbol); IBM EBCDIC (France-Euro)"; break;
				case 1148: ans = "IBM EBCDIC International (500 + Euro symbol); IBM EBCDIC (International-Euro)"; break;
				case 1149: ans = "IBM EBCDIC Icelandic (20871 + Euro symbol); IBM EBCDIC (Icelandic-Euro)"; break;
				case 1200: ans = "Unicode UTF-16, little endian byte order (BMP of ISO 10646)"; break;
				case 1201: ans = "Unicode UTF-16, big endian byte order"; break;
				case 1250: ans = "ANSI Central European; Central European (Windows)"; break;
				case 1251: ans = "ANSI Cyrillic; Cyrillic (Windows)"; break;
				case 1252: ans = "ANSI Latin 1; Western European (Windows)"; break;
				case 1253: ans = "ANSI Greek; Greek (Windows)"; break;
				case 1254: ans = "ANSI Turkish; Turkish (Windows)"; break;
				case 1255: ans = "ANSI Hebrew; Hebrew (Windows)"; break;
				case 1256: ans = "ANSI Arabic; Arabic (Windows)"; break;
				case 1257: ans = "ANSI Baltic; Baltic (Windows)"; break;
				case 1258: ans = "ANSI/OEM Vietnamese; Vietnamese (Windows)"; break;
				case 1361: ans = "Korean (Johab)"; break;
				case 10000: ans = "MAC Roman; Western European (Mac)"; break;
				case 10001: ans = "Japanese (Mac)"; break;
				case 10002: ans = "MAC Traditional Chinese (Big5); Chinese Traditional (Mac)"; break;
				case 10003: ans = "Korean (Mac)"; break;
				case 10004: ans = "Arabic (Mac)"; break;
				case 10005: ans = "Hebrew (Mac)"; break;
				case 10006: ans = "Greek (Mac)"; break;
				case 10007: ans = "Cyrillic (Mac)"; break;
				case 10008: ans = "MAC Simplified Chinese (GB 2312); Chinese Simplified (Mac)"; break;
				case 10010: ans = "Romanian (Mac)"; break;
				case 10017: ans = "Ukrainian (Mac)"; break;
				case 10021: ans = "Thai (Mac)"; break;
				case 10029: ans = "MAC Latin 2; Central European (Mac)"; break;
				case 10079: ans = "Icelandic (Mac)"; break;
				case 10081: ans = "Turkish (Mac)"; break;
				case 10082: ans = "Croatian (Mac)"; break;
				case 12000: ans = "Unicode UTF-32, little endian byte order; available only to managed applications"; break;
				case 12001: ans = "Unicode UTF-32, big endian byte order; available only to managed applications"; break;
				case 20000: ans = "CNS Taiwan; Chinese Traditional (CNS)"; break;
				case 20001: ans = "TCA Taiwan"; break;
				case 20002: ans = "Eten Taiwan; Chinese Traditional (Eten)"; break;
				case 20003: ans = "IBM5550 Taiwan"; break;
				case 20004: ans = "TeleText Taiwan"; break;
				case 20005: ans = "Wang Taiwan"; break;
				case 20105: ans = "IA5 (IRV International Alphabet No. 5, 7-bit); Western European (IA5)"; break;
				case 20106: ans = "IA5 German (7-bit)"; break;
				case 20107: ans = "IA5 Swedish (7-bit)"; break;
				case 20108: ans = "IA5 Norwegian (7-bit)"; break;
				case 20127: ans = "US-ASCII (7-bit)"; break;
				case 20261: ans = "T.61"; break;
				case 20269: ans = "ISO 6937 Non-Spacing Accent"; break;
				case 20273: ans = "IBM EBCDIC Germany"; break;
				case 20277: ans = "IBM EBCDIC Denmark-Norway"; break;
				case 20278: ans = "IBM EBCDIC Finland-Sweden"; break;
				case 20280: ans = "IBM EBCDIC Italy"; break;
				case 20284: ans = "IBM EBCDIC Latin America-Spain"; break;
				case 20285: ans = "IBM EBCDIC United Kingdom"; break;
				case 20290: ans = "IBM EBCDIC Japanese Katakana Extended"; break;
				case 20297: ans = "IBM EBCDIC France"; break;
				case 20420: ans = "IBM EBCDIC Arabic"; break;
				case 20423: ans = "IBM EBCDIC Greek"; break;
				case 20424: ans = "IBM EBCDIC Hebrew"; break;
				case 20833: ans = "IBM EBCDIC Korean Extended"; break;
				case 20838: ans = "IBM EBCDIC Thai"; break;
				case 20866: ans = "Russian (KOI8-R); Cyrillic (KOI8-R)"; break;
				case 20871: ans = "IBM EBCDIC Icelandic"; break;
				case 20880: ans = "IBM EBCDIC Cyrillic Russian"; break;
				case 20905: ans = "IBM EBCDIC Turkish"; break;
				case 20924: ans = "IBM EBCDIC Latin 1/Open System (1047 + Euro symbol)"; break;
				case 20932: ans = "Japanese (JIS 0208-1990 and 0212-1990)"; break;
				case 20936: ans = "Simplified Chinese (GB2312); Chinese Simplified (GB2312-80)"; break;
				case 20949: ans = "Korean Wansung"; break;
				case 21025: ans = "IBM EBCDIC Cyrillic Serbian-Bulgarian"; break;
				case 21027: ans = "(deprecated)"; break;
				case 21866: ans = "Ukrainian (KOI8-U); Cyrillic (KOI8-U)"; break;
				case 28591: ans = "ISO 8859-1 Latin 1; Western European (ISO)"; break;
				case 28592: ans = "ISO 8859-2 Central European; Central European (ISO)"; break;
				case 28593: ans = "ISO 8859-3 Latin 3"; break;
				case 28594: ans = "ISO 8859-4 Baltic"; break;
				case 28595: ans = "ISO 8859-5 Cyrillic"; break;
				case 28596: ans = "ISO 8859-6 Arabic"; break;
				case 28597: ans = "ISO 8859-7 Greek"; break;
				case 28598: ans = "ISO 8859-8 Hebrew; Hebrew (ISO-Visual)"; break;
				case 28599: ans = "ISO 8859-9 Turkish"; break;
				case 28603: ans = "ISO 8859-13 Estonian"; break;
				case 28605: ans = "ISO 8859-15 Latin 9"; break;
				case 29001: ans = "Europa 3"; break;
				case 38598: ans = "ISO 8859-8 Hebrew; Hebrew (ISO-Logical)"; break;
				case 50220: ans = "ISO 2022 Japanese with no halfwidth Katakana; Japanese (JIS)"; break;
				case 50221: ans = "ISO 2022 Japanese with halfwidth Katakana; Japanese (JIS-Allow 1 byte Kana)"; break;
				case 50222: ans = "ISO 2022 Japanese JIS X 0201-1989; Japanese (JIS-Allow 1 byte Kana - SO/SI)"; break;
				case 50225: ans = "ISO 2022 Korean"; break;
				case 50227: ans = "ISO 2022 Simplified Chinese; Chinese Simplified (ISO 2022)"; break;
				case 50229: ans = "ISO 2022 Traditional Chinese"; break;
				case 50930: ans = "EBCDIC Japanese (Katakana) Extended"; break;
				case 50931: ans = "EBCDIC US-Canada and Japanese"; break;
				case 50933: ans = "EBCDIC Korean Extended and Korean"; break;
				case 50935: ans = "EBCDIC Simplified Chinese Extended and Simplified Chinese"; break;
				case 50936: ans = "EBCDIC Simplified Chinese"; break;
				case 50937: ans = "EBCDIC US-Canada and Traditional Chinese"; break;
				case 50939: ans = "EBCDIC Japanese (Latin) Extended and Japanese"; break;
				case 51932: ans = "EUC Japanese"; break;
				case 51936: ans = "EUC Simplified Chinese; Chinese Simplified (EUC)"; break;
				case 51949: ans = "EUC Korean"; break;
				case 51950: ans = "EUC Traditional Chinese"; break;
				case 52936: ans = "HZ-GB2312 Simplified Chinese; Chinese Simplified (HZ)"; break;
				case 54936: ans = "Windows XP and later:?GB18030 Simplified Chinese (4 byte); Chinese Simplified (GB18030)"; break;
				case 57002: ans = "ISCII Devanagari"; break;
				case 57003: ans = "ISCII Bangla"; break;
				case 57004: ans = "ISCII Tamil"; break;
				case 57005: ans = "ISCII Telugu"; break;
				case 57006: ans = "ISCII Assamese"; break;
				case 57007: ans = "ISCII Odia"; break;
				case 57008: ans = "ISCII Kannada"; break;
				case 57009: ans = "ISCII Malayalam"; break;
				case 57010: ans = "ISCII Gujarati"; break;
				case 57011: ans = "ISCII Punjabi"; break;
				case 65000: ans = "Unicode (UTF-7)"; break;
				case 65001: ans = "Unicode (UTF-8)"; break;
				default: ans = "Unknown";
				}
				return ans;
			}


			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/03651cf7-1926-4356-b42b-a378938975e5
			class CodePageRecord : public Record {
			public:
				unsigned short codepage;

				CodePageRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					this->codepage = common::ReadUShort(this->Data.data(), this->Data.size(), 0);
				}
				
				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";
					str << "<CodePage>" << this->codepage << "</CodePage>";
					str << "<CodePageStr>" << CPToString(this->codepage) << "</CodePageStr>";
					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length << ",";
					str << "\"CodePage\":" << this->codepage << ",";
					str << "\"CodePageStr\":\"" << common::JsonEscape(CPToString(this->codepage)) << "\"";
					str << "}";
					return str.str();
				}

			};

		}
	}
}