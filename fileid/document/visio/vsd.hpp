#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"

namespace document {
	namespace visio {
		static const char VISIO[] = "Visio (TM) Drawing\x0d\x0a"; //24
		struct VsdHeader
		{
			char key[24];
			unsigned short minor;
			unsigned short major;

		};
		//Visio (.vsd) specific
		unsigned short GetVisoVersion(const std::vector<uint8_t> stream) {
			unsigned short version = 0;
			auto buffer = stream.data();

			VsdHeader* header = (VsdHeader*)buffer;
			version = header->major;

			return version;
		}
		std::string GetVersion_Visio(unsigned short version) {
			std::string ans;

			switch (version) {
			case 0xB: ans = "Visio 2003 or greater"; break;
			case 0xA: ans = "Visio 2002"; break;
			case 0x6: ans = "Visio 2000"; break;
			case 0x5: ans = "Visio 5"; break;
			case 0x4: ans = "Visio 4"; break;
			case 0x3: ans = "Visio 3"; break;
			case 0x2: ans = "Visio 2"; break;
			case 0x1: ans = "Visio 1"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}

		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			e->Version = GetVisoVersion(stream);
			e->VersionName = GetVersion_Visio(e->Version);
		}

	}
}