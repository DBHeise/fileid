#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			/*
			CSV taken from table given here: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7d9326d6-691a-4fa1-8dce-42082f38e943
			Powershell to generate case statements
				$data = Import-Csv -Path $CSVFile_FullPath;
				$data | % { $_.RecordType = [int]$_.RecordType };
				$data | sort RecordType | % { "case " + "0x{0:X2}" -f ([int]$_.RecordType) + ": r = (Record*)(new " + $_.Name +"Record(type, data)); break;"  } | Out-Clipboard
			*/
			std::string GetCountryName(unsigned short code) {
				std::string ans;
				switch (code) {
				case 0x0001: ans = "United States"; break;
				case 0x0002: ans = "Canada"; break;
				case 0x0003: ans = "Latin America, except Brazil"; break;
				case 0x0007: ans = "Russia"; break;
				case 0x0014: ans = "Egypt"; break;
				case 0x001E: ans = "Greece"; break;
				case 0x001F: ans = "Netherlands"; break;
				case 0x0020: ans = "Belgium"; break;
				case 0x0021: ans = "France"; break;
				case 0x0022: ans = "Spain"; break;
				case 0x0024: ans = "Hungary"; break;
				case 0x0027: ans = "Italy"; break;
				case 0x0029: ans = "Switzerland"; break;
				case 0x002B: ans = "Austria"; break;
				case 0x002C: ans = "United Kingdom"; break;
				case 0x002D: ans = "Denmark"; break;
				case 0x002E: ans = "Sweden"; break;
				case 0x002F: ans = "Norway"; break;
				case 0x0030: ans = "Poland"; break;
				case 0x0031: ans = "Germany"; break;
				case 0x0034: ans = "Mexico"; break;
				case 0x0037: ans = "Brazil"; break;
				case 0x003D: ans = "Australia"; break;
				case 0x0040: ans = "New Zealand"; break;
				case 0x0042: ans = "Thailand"; break;
				case 0x0051: ans = "Japan"; break;
				case 0x0052: ans = "Korea"; break;
				case 0x0054: ans = "Viet Nam"; break;
				case 0x0056: ans = "People's Republic of China"; break;
				case 0x005A: ans = "Turkey"; break;
				case 0x00D5: ans = "Algeria"; break;
				case 0x00D8: ans = "Morocco"; break;
				case 0x00DA: ans = "Libya"; break;
				case 0x015F: ans = "Portugal"; break;
				case 0x0162: ans = "Iceland"; break;
				case 0x0166: ans = "Finland"; break;
				case 0x01A4: ans = "Czech Republic"; break;
				case 0x0376: ans = "Taiwan"; break;
				case 0x03C1: ans = "Lebanon"; break;
				case 0x03C2: ans = "Jordan"; break;
				case 0x03C3: ans = "Syria"; break;
				case 0x03C4: ans = "Iraq"; break;
				case 0x03C5: ans = "Kuwait"; break;
				case 0x03C6: ans = "Saudi Arabia"; break;
				case 0x03CB: ans = "United Arab Emirates"; break;
				case 0x03CC: ans = "Israel"; break;
				case 0x03CE: ans = "Qatar"; break;
				case 0x03D5: ans = "Iran"; break;
				default: ans = "Unknown";
				}
				return ans;
			}


			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/440b4cc6-215f-439a-af5b-f1b666c1af78
			// The Country record specifies locale information for a workbook.
			class CountryRecord : public Record {
			private:
				unsigned short iCountryDef;
				unsigned short iCountryWinIni;
			public:
				CountryRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					this->iCountryDef = common::ReadUShort(buffer, max, 0);
					this->iCountryWinIni = common::ReadUShort(buffer, max, 2);					
				}
				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<WorkbookLocale><Code>" << this->iCountryDef << "</Code><Name>" << GetCountryName(this->iCountryDef) << "</Name></WorkbookLocale>";
					str << "<OSLocale><Code>" << this->iCountryWinIni << "</Code><Name>" << GetCountryName(this->iCountryWinIni) << "</Name></OSLocale>";
					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"WorkbookLocale\" : { \"Code\":" << this->iCountryDef << ", \"Name\": \"" << GetCountryName(this->iCountryDef) << "\"}";
					str << ",\"OSLocale\" : { \"Code\":" << this->iCountryWinIni << ", \"Name\": \"" << GetCountryName(this->iCountryWinIni) << "\"}";
					str << "}";
					return str.str();
				}
			};
		}
	}
}
