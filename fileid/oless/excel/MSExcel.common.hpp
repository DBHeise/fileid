#pragma once

#include "../../common.hpp"
#include "../OleCommon.hpp"

namespace oless {
	namespace excel {

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