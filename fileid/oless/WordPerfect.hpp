#pragma once

#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"
#include "../document/wp/wordperfect.hpp"


namespace OleStructuredStorage {
	namespace WordPerfect {


		common::ExtensionInfo* ReadWPStream(POLE::Stream* stream) {
			auto ans = new document::wp::WordPerfectExtensionInfo();
			ans->Header = OleHelper::GetStructFromStream<document::wp::wpheader>(stream);
			return ans;
		}

	}
}