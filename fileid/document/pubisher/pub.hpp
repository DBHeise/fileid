#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"

namespace document {
	namespace publisher {

		struct PubHeader {
			unsigned short one;
			unsigned short two;
			unsigned short version0;
			unsigned short version1;
			unsigned long unkown;
			unsigned short version2;
		};
		//Publisher (.pub) specific
		unsigned short GetPubVersion(std::vector<uint8_t> stream) {
			unsigned short version = 0;

			auto buffer = stream.data();
			auto max = stream.size();
			unsigned int index = 0;

			PubHeader* header = (PubHeader*)buffer;
			version = header->version0;

			if (version == 300) {
				version = header->version2;
			}

			return version;
		}
		std::string GetVersion_Publisher(unsigned short version) {
			std::string ans;

			switch (version) {
			case 125: ans = "Publisher 3"; break;
			case 136: ans = "Publisher 4"; break;
			case 616: ans = "Publisher 5"; break;
			case 717: ans = "Publisher 6"; break;
			case 1000: ans = "Publisher 10"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}

		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			e->Version = GetPubVersion(stream);
			e->VersionName = GetVersion_Publisher(e->Version);
		}		
	}
}