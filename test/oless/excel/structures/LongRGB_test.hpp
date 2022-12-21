#pragma once
#include "../../../doctest.h"
#include "../../../../fileid/document/excel/structures/LongRGB.hpp"

TEST_SUITE("LongRGB") {
	TEST_CASE("cTor") {
		auto t = new oless::excel::structures::LongRGB();		
	}
	TEST_CASE("Parse") {
		auto t = new oless::excel::structures::LongRGB();
		unsigned char buffer[4] = { 0x0A, 0x0B, 0x0C, 0x0D };
		t->Parse((unsigned char*)&buffer, 4, 0);
		CHECK_EQ(t->bytesRead, 4);
		CHECK_EQ(t->red, 0x0A);
		CHECK_EQ(t->green, 0x0B);
		CHECK_EQ(t->blue, 0x0C);
		CHECK_EQ(t->reserved, 0x0D);
	}
	TEST_CASE("ToText") {
		auto t = new oless::excel::structures::LongRGB();
		unsigned char buffer[4] = { 0x0A, 0x0B, 0x0C, 0x0D };
		t->Parse((unsigned char*)&buffer, 4, 0);
		CHECK_EQ(t->ToText(), "#0A0B0C0D");
	}
}