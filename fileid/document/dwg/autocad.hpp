#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"

namespace document {
	namespace dwg {

		std::vector<common::ExtensionInfo*> DwgHelper(const std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;
			common::ExtensionInfo* ei = new common::ExtensionInfo();
			ei->Extension = "dwg";

			if (buffer.size() > 5) {

				if (buffer[4] == 0x30) {
					if (buffer[5] == 0x32)
						ei->VersionName = "AutoCAD R2.5";
					else if (buffer[5] == 0x33)
						ei->VersionName = "AutoCAD R2.6";
					else if (buffer[5] == 0x34)
						ei->VersionName = "AutoCAD R9";
					else if (buffer[5] == 0x36)
						ei->VersionName = "AutoCAD R10";
					else if (buffer[5] == 0x39)
						ei->VersionName = "AutoCAD R11/R12";
				}
				else if (buffer[4] == 0x31) {
					if (buffer[5] == 0x30)
						ei->VersionName = "AutoCAD R13 (subtype 10)";
					else if (buffer[5] == 0x31)
						ei->VersionName = "AutoCAD R13 (subtype 11)";
					else if (buffer[5] == 0x32)
						ei->VersionName = "AutoCAD R13 (subtype 12)";
					else if (buffer[5] == 0x33)
						ei->VersionName = "AutoCAD R14 (subtype 13)";
					else if (buffer[5] == 0x34)
						ei->VersionName = "AutoCAD R14 (subtype 14)";
					else if (buffer[5] == 0x35)
						ei->VersionName = "AutoCAD R2000";
					else if (buffer[5] == 0x38)
						ei->VersionName = "AutoCAD R2004";
				}
				else if (buffer[4] == 0x32) {
					if (buffer[5] == 0x31)
						ei->VersionName = "AutoCAD R2007";
				}
			}
			ans.push_back(ei);
			return ans;
		}


	}

}