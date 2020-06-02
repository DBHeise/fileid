#pragma once
#include <fstream>
#include <random>
#include <vector>

namespace testhelper {
	std::random_device rd{};
	std::mt19937 gen{ rd() };

	unsigned char* randomBuffer(size_t size) {
		unsigned char* buffer = new unsigned char[size];

		std::uniform_int_distribution<int> d(0, 255);

		for (size_t i = 0; i < size; i++) {
			buffer[i] = (char)(d(gen));
		}

		return buffer;
	}

	std::string GetTestFileFolder() {
		char const* val = getenv("TESTFOLDER");
		return val == nullptr ? std::string("") : std::string(val);
	}

	std::string GetTestFile(std::string filekey) {
		return GetTestFileFolder() + filekey;
	}
}