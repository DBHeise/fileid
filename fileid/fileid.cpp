// fileid.cpp 
// 2015-10-13 09:32:53Z
//

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "common.hpp"
#include "magic.h"
#include "details.hpp"


void dumpFile(std::string file) {

	std::vector<unsigned char> buffer = common::readFile(file, 512);
	common::hexDump(file.c_str(), buffer.data(), buffer.size());
}

void showUsage() {
	std::cout << "fileid {file} [format]" << std::endl;
}

common::ExtraDataFunc GetExtraDataFunction(std::string name) {
	common::ExtraDataFunc ans = NULL;
	if (name == "DwgHelper") {
		ans = details::DwgHelper;
	}
	else if (name == "ExeHelper") {
		ans = details::ExeHelper;
	}
	else if (name == "JpegHelper") {
		ans = details::JpegHelper;
	}
	else if (name == "Mp4Helper") {
		ans = details::Mp4Helper;
	}
	else if (name == "OleHelper") {
		ans = details::OleHelper;
	}
	else if (name == "ZipHelper") {
		ans = details::ZipHelper;
	}
	else {
		throw std::exception("Unknown Extra Data Funcion (bad dev)");
	}

	return ans;
}

bool checkMagic(const unsigned char* actual, unsigned int actualLength, const unsigned char* expected, unsigned int expectedLength, unsigned int offset) {
	bool ans = true;

	unsigned int min = expectedLength;
	unsigned int max = actualLength;
	const unsigned char* minner = expected;
	const unsigned char* maxxer = actual;
	if (expectedLength > actualLength) {
		min = actualLength;
		max = expectedLength;
		minner = actual;
		maxxer = expected;
	}

	if (offset + min > max)
		return false;

	for (unsigned int i = offset; i < (min + offset) && ans; i++)
		ans &= maxxer[i] == minner[i - offset];

	return ans;
}

std::vector<common::ExtensionInfo*> guessExtension(std::string file) {
	std::vector<common::ExtensionInfo*> ans;
	std::vector<unsigned char> buffer = common::readFile(file, 512);

	for (common::MagicInfo &mi : list) {
		if (checkMagic(buffer.data(), (unsigned int)buffer.size(), mi.magic, mi.size, mi.offset)) {
			if (mi.extraName.size() > 0) {
				common::ExtraDataFunc func = GetExtraDataFunction(mi.extraName);
				std::vector<common::ExtensionInfo*> list2 = func(file, buffer);
				for (common::ExtensionInfo* i : list2) {
					ans.push_back(i);
				}
			}
			else {
				common::ExtensionInfo* ei = new common::ExtensionInfo();
				ei->Extension = mi.Extension;
				ei->VersionName += mi.Name;
				if (mi.Version.size() > 0) {
					ei->VersionName += " (";
					ei->VersionName += mi.Version;
					ei->VersionName += ")";
				}
				ans.push_back(ei);
			}
		}
	}
	return ans;
}

common::ExtensionInfo* UnknownExtension(std::string file) {
	common::ExtensionInfo* ei = new common::ExtensionInfo();
	ei->Extension = "unknown";
	ei->VersionName = "Unknown";
	//get dump
	return ei;
}

int main(int argc, char* argv[])
{
	std::vector<std::string> params(argv + 1, argv + argc);
	if (argc > 1) {
		std::string file = params[0];
		common::OutputFormat outFormat = common::OutputFormat::TEXT;
		if (argc > 2) { outFormat = common::ParseOutputFormat(argv[2]); }
		std::vector<common::ExtensionInfo*> extensions = guessExtension(file);
		if (extensions.size() == 0) {
			extensions.push_back(UnknownExtension(file));
		}
		common::Output<common::ExtensionInfo>(outFormat, file, "extensions", extensions);
	}
	else {
		showUsage();
	}

	return 0;
}
