#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../testhelp.hpp"
#include "../../fileid/oless/OleCommon.hpp"

TEST_SUITE("olecommon") {

	std::string testfile = "C:\\dev.public\\fileid.testfiles\\oless\\File001.oless";

	TEST_CASE("OpenFile") {
		auto storage = oless::OpenFile(testfile.c_str());
		CHECK(storage);

		auto entries = storage->entries(L"/");
		CHECK_EQ(entries.size(), 4);
		storage->close();
	}

	TEST_CASE("ReadStream") {
		auto storage = oless::OpenFile(testfile.c_str());
		auto stream = oless::ReadStream(storage, L"/Storage1/Storage2/Stream2");
		CHECK_EQ(stream.size(), 256);

		CHECK_EQ(stream[10], 0xF5);
		CHECK_EQ(stream[101], 0x9A);
		CHECK_EQ(stream[242], 0x0D);

		storage->close();
	}
}