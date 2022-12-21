#pragma once
#include <fstream>
#include <random>
#include <vector>

#ifdef WIN32
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

#include "doctest.h"

namespace testhelper {
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	bool ListContains(std::vector<std::string> list, std::string name) {
		return std::find(list.begin(), list.end(), name) != list.end();
	}
	bool ListContains(std::vector<std::wstring> list, std::wstring name) {
		return std::find(list.begin(), list.end(), name) != list.end();
	}

	//randomBuffer - returns an unsigned char array of specified size filled with random bytes
	unsigned char* randomBuffer(size_t size) {
		unsigned char* buffer = new unsigned char[size];

		std::uniform_int_distribution<int> d(0, 255);

		for (size_t i = 0; i < size; i++) {
			buffer[i] = (char)(d(gen));
		}

		return buffer;
	}
	//GetTestFileFolder - returns the folder that contains the test files; should be called from within a TEST_CASE as it does assert
	std::string GetTestFileFolder() {
		char const* val = getenv("TESTFOLDER");		
		REQUIRE_MESSAGE(val != nullptr, "Environment variable TESTFOLDER is not set...all file-based tests will fail");
		return val == nullptr ? std::string("") : std::string(val);
	}

	//GetTestFile - returns the path to the requested file; should be called from within a TEST_CASE as it does assert
	std::string GetTestFile(std::string filekey) {
		fs::path p = GetTestFileFolder();
		p /= filekey;
		REQUIRE_MESSAGE(fs::exists(p), "The requested test file does not exist!");
		return p.generic_string();
	}
}