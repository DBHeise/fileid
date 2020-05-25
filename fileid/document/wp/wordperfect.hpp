#pragma once
#include <string>
#include <vector>
#include <map>
#include "../../common.hpp"


namespace document {
	namespace wp {

		struct wpheader {
			unsigned long magic;
			unsigned long doc_ptr;
			unsigned char prod_type;
			unsigned char file_type;
			unsigned char major_ver;
			unsigned char minor_ver;
			unsigned int encrypt;
			unsigned int idxoffset;
		};

		std::string fileTypeToString(unsigned char file_type) {
			switch (file_type)
			{
			case 0x01: { return "Macro file"; break; }
			case 0x02: { return "Help file"; break; }
			case 0x03: { return "Keyboard definition file"; break; }
			case 0x04: { return "VAX keyboard definition file added for WP 5.1"; break; }
			case 0x0A: { return "WordPerfect document"; break; }
			case 0x0B: { return "Dictionary file"; break; }
			case 0x0C: { return "Thesaurus file"; break; }
			case 0x0D: { return "Block"; break; }
			case 0x0E: { return "Rectangular block"; break; }
			case 0x0F: { return "Column block"; break; }
			case 0x10: { return "Printer resource file"; break; }
			case 0x11: { return "Setup file [contains the system values for WP{WP}.SET"; break; }
			case 0x12: { return "Reserved"; break; }
			case 0x13: { return "Printer resource file"; break; }
			case 0x14: { return "Display resource file"; break; }
			case 0x15: { return "Overlay file"; break; }
			case 0x16: { return "WP graphic file"; break; }
			case 0x17: { return "Hyphenation code module"; break; }
			case 0x18: { return "Hyphenation data module"; break; }
			case 0x19: { return "Macro resource file"; break; }
			case 0x1A: { return "Graphics screen-driver file"; break; }
			case 0x1B: { return "Hyphenation lex module"; break; }
			case 0x1C: { return "Printer Q codes"; break; }
			case 0x1D: { return "Spell code module word list"; break; }
			case 0x1E: { return "WP.QRS file"; break; }
			case 0x1F: { return "Reserved"; break; }
			case 0x20: { return "VAX.SET"; break; }
			case 0x21: { return "Spell code module rules"; break; }
			case 0x22: { return "Dictionary rules"; break; }
			case 0x23: { return "Reserved"; break; }
			case 0x24: { return ".WPD files"; break; }
			case 0x25: { return "Rhymer word file"; break; }
			case 0x26: { return "Rhymer pronunciation file"; break; }
			case 0x27: { return "Reserved"; break; }
			case 0x28: { return "Reserved"; break; }
			case 0x29: { return "WP 51.INS file"; break; }
			case 0x2A: { return "Mouse driver for WP5.1"; break; }
			case 0x2B: { return "UNIX setup file for WP5.0"; break; }
			case 0x2C: { return "Macintosh WP2.0 document"; break; }
			case 0x2D: { return "VAX file"; break; }
			case 0x2E: { return "External spell code module"; break; }
			case 0x2F: { return "External spell dictionary"; break; }
			case 0x30: { return "Macintosh SOFT graphics file"; break; }
			case 0x31: { return "Reserved"; break; }
			case 0x37: { return "Reserved"; break; }
			case 0x38: { return "WPWin 5.1 Application Resource Library added for WPWin 5.1"; break; }
			default:
				return "Unknown File Type: " + std::to_string(file_type);
				break;
			}
		}


		class WordPerfectExtensionInfo : public common::ExtensionInfo {
		public:
			WordPerfectExtensionInfo() {
				this->Extension = "wp";
				this->VersionName = "Word Perfect File";
			}

			wpheader* Header;

			virtual std::string ToJson() const override {
				std::ostringstream str;
				str << "{";
				str << this->buildBaseJson();
				str << ", \"Header\": {";
				str << "\"ProductType\":\"" << (unsigned short)this->Header->prod_type << "\"";
				str << ",\"FileType\":\"" << fileTypeToString(this->Header->file_type) << "\"";
				str << ",\"MajorVersion\":\"" << (unsigned short)this->Header->major_ver << "\"";
				str << ",\"MinorVersion\":\"" << (unsigned short)this->Header->minor_ver << "\"";
				str << ",\"Encrypt\":\"" << this->Header->encrypt << "\"";
				str << "}}";
				return str.str();
			}
			virtual std::string ToXml() const override {
				std::ostringstream str;
				str << "<item>";
				str << this->buildBaseXml();
				str << "<Header>";
				str << "<ProductType>" << (unsigned short)this->Header->prod_type << "</ProductType>";
				str << "<FileType>" << fileTypeToString(this->Header->file_type) << "</FileType>";
				str << "<MajorVersion>" << (unsigned short)this->Header->major_ver << "</MajorVersion>";
				str << "<MinorVersion>" << (unsigned short)this->Header->minor_ver << "</MinorVersion>";
				str << "<Encrypt>" << this->Header->encrypt << "<Encrypt>";
				str << "</Header>";
				str << "</item>";
				return str.str();
			}
			virtual std::string ToText() const override {
				std::ostringstream str;
				str << this->Extension;
				str << "\t" << this->VersionName;
				str << "\t" << this->Version;
				return str.str();
			}
			virtual std::string ToCsv() const override {
				std::ostringstream str;
				str << this->Extension;
				str << "," << this->VersionName;
				str << "," << this->Version;
				return str.str();
			}

		};

		std::vector<common::ExtensionInfo*> Detailer(std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;
			WordPerfectExtensionInfo* info = new WordPerfectExtensionInfo();
			
			wpheader* head = (wpheader*)buffer.data();
			info->Header = head;

			ans.push_back(info);
			return ans;
		}
	
	}
}
