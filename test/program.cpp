
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "..\fileid\common.hpp"



TEST_SUITE("checkMagic") {
	TEST_CASE("basic functionality") {
		unsigned char actual[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

		unsigned char exp_a[] = { 0x01, 0x02, 0x03, 0x04 };
		unsigned char exp_b[] = { 0x01, 0x02, 0x03, 0xA4 };
		unsigned char exp_c[] = { 0x02, 0x03, 0x04, 0x05 };
		unsigned char exp_d[] = { 0x06, 0x07 };
		unsigned char exp_e[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };

		SUBCASE("simple pass") {
			CHECK(common::checkMagic(actual, 8, exp_a, 4, 0) == true);
		}
		SUBCASE("simple fail") {
			CHECK(common::checkMagic(actual, 8, exp_b, 4, 0) == false);
		}
		SUBCASE("offset") {
			CHECK(common::checkMagic(actual, 8, exp_c, 4, 1) == true);
		}
		SUBCASE("offset past end") {
			CHECK(common::checkMagic(actual, 8, exp_d, 2, 7) == false);
		}
		SUBCASE("expected longer than actual") {
			CHECK(common::checkMagic(actual, 8, exp_e, 9, 0) == false);
		}
	}
}