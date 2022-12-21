#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"
#include "testhelp.hpp"


#include "common_test.hpp"
#include "oless/excel/structures/LongRGB_test.hpp"

int main(int argc, char** argv) {
	doctest::Context context;

	context.setOption("order-by", "file");            // sort the test cases by file and line
	context.applyCommandLine(argc, argv);

	int res = context.run();
	return res;
}