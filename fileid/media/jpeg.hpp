#pragma once
#include <string>
#include <vector>
#include "../common.hpp"

namespace media {
	namespace jpeg {
		std::vector<common::ExtensionInfo*> Detailer(const std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;
			common::ExtensionInfo* ei = new common::ExtensionInfo();
			ei->Extension = "jpg";
			ans.push_back(ei);
			return ans;
		}
	}
}
