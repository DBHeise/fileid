#pragma once

#include "../../common.hpp"
#include "../../oless/OleCommon.hpp"

namespace oless {
	namespace excel {

		enum class ExcelVersion: unsigned short {
			Unknown = 0,
			BIFF2 = 512,
			BIFF3 = 768,
			BIFF4 = 1024,
			BIFF5 = 1280,
			BIFF8 = 1536
		};

		std::string GetVersionFromVer(ExcelVersion version) {
			std::string ans;

			switch (version) {
			case ExcelVersion::BIFF2: ans = "BIFF2"; break;
			case ExcelVersion::BIFF3: ans = "BIFF3"; break;
			case ExcelVersion::BIFF4: ans = "BIFF4"; break;
			case ExcelVersion::BIFF5: ans = "BIFF5"; break;
			case ExcelVersion::BIFF8: ans = "BIFF8"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}
		std::string GetVersion_Excel(unsigned short version) {
			return GetVersionFromVer(static_cast<ExcelVersion>(version));
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
			case 0x00: ans = "Worksheet/Dialog"; break;
			case 0x01: ans = "Macro sheet"; break;
			case 0x02: ans = "Chart sheet"; break;
			case 0x06: ans = "VBA Module"; break;
			default: ans = "Unknown/Undocumented type"; break;
			}
			return ans;
		}

		double ReadXNumFromBytes(unsigned char* buffer) {
			union {
				unsigned char data[8];
				double num;
			};
			for (int i = 0; i < 8; i++)
			{
				data[i] = buffer[i];
			}
			return num;
		}

		std::string ColNumToName(const unsigned short col) {
			std::string ans;
			ans.reserve(4);
			unsigned short n = col;
			while (n > 0) {
				ans.insert(0, 1, (char)(65 + (n - 1) % 26));
				n = (n - 1) / 26;
			}
			return ans;
		}


	}
}