// fileid.cpp 
// 2015-10-13 09:32:53Z
//

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
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
	else if (name == "RIFFHelper") {
		ans = details::RIFFHelper;
	}
	else if (name == "ASFHelper") {
		ans = details::ASFHelper;
	}
	else {
		throw std::logic_error("Unknown Extra Data Funcion (bad dev)");
	}

	return ans;
}



std::vector<common::ExtensionInfo*> guessExtension(std::string file) {
	std::vector<common::ExtensionInfo*> ans;
	std::vector<unsigned char> buffer = common::readFile(file, 512);

	if (buffer.size() > 0) {
		for (std::vector<common::MagicInfo>::const_iterator i = list.begin(); i != list.end(); i++) {
			common::MagicInfo mi = *i;
			if (common::checkMagic(buffer.data(), (unsigned int)buffer.size(), mi.magic, mi.size, mi.offset)) {
				if (mi.extraName.size() > 0) {
					common::ExtraDataFunc func = GetExtraDataFunction(mi.extraName);
					std::vector<common::ExtensionInfo*> list2 = func(file, buffer);
					for (std::vector<common::ExtensionInfo*>::const_iterator n = list2.begin(); n != list2.end(); n++) {
						ans.push_back(*n);
					}
				}
				else {
					common::ExtensionInfo* ei = new common::ExtensionInfo();
					ei->Extension = mi.Extension;
					ei->Name += mi.Name;
					if (mi.Version.size() > 0) {
						ei->SubType = mi.Version;
					}
					ans.push_back(ei);
				}
			}
		}
	}	return ans;
}

common::ExtensionInfo* UnknownExtension(std::string file) {
	common::ExtensionInfo* ei = new common::ExtensionInfo();
	std::vector<unsigned char> buffer = common::readFile(file, 512);

	if (buffer.size() > 0) {
		ei->Extension = "unknown";
		ei->Name = "Unknown";
		std::string start(reinterpret_cast<char*>(&buffer[0]), buffer.size());
		ei->SubType = start;
	}
	else {
		ei->Extension = "empty";
		ei->Name = "Empty File";
	}

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
