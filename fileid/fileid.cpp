﻿// fileid.cpp 
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
#include "unknown.hpp"

void showUsage() {
	std::cout << "fileid {file} [format]" << std::endl;
}

//Taken from: https://stackoverflow.com/a/466242/13124
unsigned int roundUpPowerOfTwo(const unsigned int x) {
	unsigned int v = x; // compute the next highest power of 2 of 32-bit v

	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

unsigned int getMinimumBufferSize() {
	unsigned int ans = STD_BUFFER_SIZE;	
	for (auto i = magic::list.begin(); i != magic::list.end(); i++)
	{
		common::MagicInfo mi = **i;
		unsigned int size = mi.size + mi.offset;
		if (size > ans) {
			ans = size;
		}
	}
	return roundUpPowerOfTwo(ans);
}

std::vector<common::ExtensionInfo*> guessExtension(std::string file) {
	std::vector<common::ExtensionInfo*> ans;
	magic::initList();
	std::vector<unsigned char> buffer = common::readFile(file, getMinimumBufferSize());

	if (buffer.size() > 0) {
		for (auto i = magic::list.begin(); i != magic::list.end(); i++) {
			common::MagicInfo mi = **i;
			if (common::checkMagic(buffer.data(), (unsigned int)buffer.size(), mi.magic, mi.size, mi.offset)) {
				//std::cout << "Magic Match: " << mi.Name << ":" << mi.extraName << std::endl;
				if (mi.extraFunc != nullptr) {
					common::ExtraDataFunc func = *mi.extraFunc;
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
		delete ei;
		ei = new UnknownExtensionInfo(buffer);
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
