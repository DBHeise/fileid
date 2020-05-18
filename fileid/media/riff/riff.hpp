#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"

namespace media {
	namespace riff {
		std::vector<common::ExtensionInfo*> RIFFHelper(const std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;
			unsigned char magic_cda[8] = { 0x43, 0x44, 0x44, 0x41, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
			unsigned char magic_wav[8] = { 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
			unsigned char magic_avi[8] = { 0x41, 0x56, 0x49, 0x20, 0x4C, 0x49, 0x53, 0x54 }; //at offset 8, only if magic_riff
			unsigned char magic_qcp[8] = { 0x51, 0x4C, 0x43, 0x4D, 0x66, 0x6D, 0x74, 0x20 }; //at offset 8, only if magic_riff
			unsigned char magic_rmi[8] = { 0x52, 0x4D, 0x49, 0x44, 0x64, 0x61, 0x74, 0x61 }; //at offset 8, only if magic_riff
			common::ExtensionInfo* ei = new common::ExtensionInfo();

			unsigned char* data = buffer.data();
			auto size = buffer.size();

			if (common::checkMagic(data, size, magic_cda, 8, 8))
				ei->Extension = "cda";
			else if (common::checkMagic(data, size, magic_wav, 8, 8))
				ei->Extension = "wav";
			else if (common::checkMagic(data, size, magic_avi, 8, 8))
				ei->Extension = "avi";
			else if (common::checkMagic(data, size, magic_qcp, 8, 8))
				ei->Extension = "qcp";
			else if (common::checkMagic(data, size, magic_rmi, 8, 8))
				ei->Extension = "rmi";
			else
				ei->Extension = "riff";

			ans.push_back(ei);
			return ans;
		}
	}
}