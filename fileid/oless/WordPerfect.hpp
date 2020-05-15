#pragma once

#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"
#include "../misc/wordperfect.hpp"


namespace OleStructuredStorage {
	namespace WordPerfect {


		common::ExtensionInfo* ReadWPStream(POLE::Stream* stream) {
			auto ans = new misc::wp::WordPerfectExtensionInfo();
			ans->Header = OleHelper::GetStructFromStream<misc::wp::wpheader>(stream);
			return ans;
		}

	}
}