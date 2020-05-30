#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"

namespace document {
	namespace msi {
		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			std::string streamStr(stream.begin(), stream.end());
			if (streamStr.find("ModuleAdminExecuteSequence", 0) != std::string::npos) {
				e->Extension = "msm";
				e->Name = "Microsoft Installer Merge File";
			} else if (streamStr.find("InstallExecuteSequence", 0) != std::string::npos) {
				//definately an MSI
			} else if (streamStr.find("MsiPatchSequence", 0) != std::string::npos) {
				e->Extension = "msp";
				e->Name = "Microsoft Installer Patch File";
			}
		}
	}
}