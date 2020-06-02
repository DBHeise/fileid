#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../testhelp.hpp"
#include "../../fileid/oless/oless.hpp"
#include <algorithm>

TEST_SUITE("olessfile") {
	std::vector<unsigned char> fakebuffer;
	TEST_CASE("File001") {
		std::string testfile = testhelper::GetTestFile("oless/File001.oless");		
		auto result = oless::Detailer(testfile.c_str(), fakebuffer);
		REQUIRE_EQ(result.size(), 1);
		
		auto extension = result[0];
		CHECK_EQ(extension->Extension, "oless");
		if (oless::OLESSExtensionInfo* e = dynamic_cast<oless::OLESSExtensionInfo*>(extension)) {
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Stream1"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Stream5"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage1/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage1/Stream3"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage1/Storage2/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage1/Storage2/Stream2"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage 3/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage 3/Stream6"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage 3/Stream7"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/Storage 3/Stream8"), "Stream/Storage not found in paths");
		} else {
			REQUIRE_MESSAGE(FALSE, "Extenion could not be cast to OLESSExtensionInfo");
		}
	}

	TEST_CASE("File002") {
		std::string testfile = testhelper::GetTestFile("oless/File002.oless");
		auto result = oless::Detailer(testfile.c_str(), fakebuffer);
		REQUIRE_EQ(result.size(), 1);
		auto extension = result[0];
		CHECK_EQ(extension->Extension, "oless");
		if (oless::OLESSExtensionInfo* e = dynamic_cast<oless::OLESSExtensionInfo*>(extension)) {
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u0005BffeaaaaAaaaaadaAaaaaaaaGc"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/002/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/002/\u0005PebiesnrMkudrfcoIaamtykdDa"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/003/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/003/\u0005DocumentSummaryInformation"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/004/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/004/\u0005DocumentSummaryInformation"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/005/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/005/\u0005SummaryInformation"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/006/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/006/\u0005OzngklrtOwudrp0bAayojd1qWh"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/007/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/007/\u0005QebiesnrMkudrfcoIaamtykdDa"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/008/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/008/\u0005RebiesnrMkudrfcoIaamtykdDa"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/009/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/009/\u0005SebiesnrMkudrfcoIaamtykdDa"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/one"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/six"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/ten"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/two"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/five"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/four"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/nine"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/eight"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/seven"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/three"), "Stream/Storage not found in paths");

			//TODO: Verify PropertySets

		} else {
			REQUIRE_MESSAGE(FALSE, "Extenion could not be cast to OLESSExtensionInfo");
		}
	}

	TEST_CASE("File003") {
		std::string testfile = testhelper::GetTestFile("oless/File003.oless");
		auto result = oless::Detailer(testfile.c_str(), fakebuffer);
		REQUIRE_EQ(result.size(), 1);
		auto extension = result[0];
		CHECK_EQ(extension->Extension, "oless");
		if (oless::OLESSExtensionInfo* e = dynamic_cast<oless::OLESSExtensionInfo*>(extension)) {
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\uAB87\uABB0\uAB96\uAB95\uAB83\uAB76\uAB80\uAB73\uABB2\uAB83\uABBD\uAB78"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u044D\u0442\u0441\u044C\u0438a\u0301\u0438\u0436\u0424\u041B\u0301\u0445"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u0662\u0668\u067E\u064F\u0686\u0633\u06AD\u0698\u064C\u064C\u24D8\u0624\u200D\u06A5\u200C"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u5A92\u984D\u8CC4\u5BD2\u30F4\u64C1\u9B45\u6982\u3055\u8CDE\u5631\u8A9E\u53C2\u98DB\u50B5"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u4ED6\u5371\u7518\u8AFA-\u66FC\u6CCA\u51B0-\u5F26\u591A\u4F54\u78A9\u8B1B\u8CB4\u96AA"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u05D1\u05E4\u05D4\u05E6\u05E1\u05E8\u05D3\u05D1\u05E1\u05D8\u05DC\u05D9\u05E5\u05DC\u05EA\u05D6\u05E9"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u0E1F\u0E33\u0E12\u0E14\u0E01\u0E1F\u0E2B\u0E11\u0E24\u0E0F\u0E4A\u0E1E\u0E44\u0E09\u0E03\u0E36\u0E32"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u0943\u0913\u092A\u090B\u0921\u0902\u0911\u093E\u0950\u090F\u0919\u092A\u093C\u0907\u0944\u0924\u091D\u0919\u0937"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u0F72\u0F58\u0F5E\u0FAE\u0F58\u0F7F\u0FAB\u0FB7\u0F7E\u0F59\u0F77\u0F94\u0F63\u0FBC\u0F90\u0F77\u0F59\u0FB5\u0F4F"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/001/\u1030\u100A\u1042\u1017\u1011\u1012\u105A\u1033\u103A\u1012\u101A\u1014\u1018\u103D\u1041\u1019\u1014"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/os6lt"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/iMSeJxBNXSw"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/tZxxLxBbkxEyM"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/2yurLQYjzqMi9L"), "Stream/Storage not found in paths");
			CHECK_MESSAGE(testhelper::ListContains(e->paths, L"/GrsdTKswuOwh1v2sAb"), "Stream/Storage not found in paths");

		} else {
			REQUIRE_MESSAGE(FALSE, "Extenion could not be cast to OLESSExtensionInfo");
		}
	}
}