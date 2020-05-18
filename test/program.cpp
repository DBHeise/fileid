#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <fstream>
#include <random>
#include "..\fileid\common.hpp"

std::random_device rd{};
std::mt19937 gen{ rd() };

int main(int argc, char** argv) {
	doctest::Context context;
	
	context.applyCommandLine(argc, argv);

	int res = context.run();
	if (context.shouldExit())
		return res;

	return res;
}


TEST_SUITE("common") {
	TEST_CASE("checkMagic") {
		SUBCASE("basic") {
			unsigned char actual[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

			unsigned char exp_a[] = { 0x01, 0x02, 0x03, 0x04 };
			unsigned char exp_b[] = { 0x01, 0x02, 0x03, 0xA4 };
			unsigned char exp_c[] = { 0x02, 0x03, 0x04, 0x05 };
			unsigned char exp_d[] = { 0x06, 0x07 };
			unsigned char exp_e[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };

			SUBCASE("simple pass") {
				CHECK(common::checkMagic(actual, 8, exp_a, 4, 0));
			}
			SUBCASE("simple fail") {
				CHECK_FALSE(common::checkMagic(actual, 8, exp_b, 4, 0));
			}
			SUBCASE("offset") {
				CHECK(common::checkMagic(actual, 8, exp_c, 4, 1));
			}
			SUBCASE("offset past end") {
				CHECK_FALSE(common::checkMagic(actual, 8, exp_d, 2, 7));
			}
			SUBCASE("expected longer than actual") {
				CHECK_FALSE(common::checkMagic(actual, 8, exp_e, 9, 0));
			}
		}
	}
	TEST_CASE("FileTimeToString") {
		SUBCASE("basic") {
			SUBCASE("zero") {
				CHECK(common::FileTimeToString(0) == "1601-01-01 00:00:00");
			}
			SUBCASE("one") {
				CHECK(common::FileTimeToString(1) == "1601-01-01 00:00:00");
			}
			SUBCASE("normal") {
				CHECK(common::FileTimeToString(132223284000000000) == "2020-01-01 00:00:00");
			}
		}
	}
	TEST_CASE("displayDuration") {
		SUBCASE("basic") {
			SUBCASE("zero") {
				CHECK(common::displayDuration(0) == "00:00:00");
			}
			SUBCASE("3 days") {
				CHECK(common::displayDuration(2592000000000) == "72:00:00");
			}
			SUBCASE("exact") {
				CHECK(common::displayDuration(1657127941371) == "46:01:52.794137");
			}
		}
	}
	TEST_CASE("iequals") {
		SUBCASE("basic") {
			SUBCASE("empty") {
				CHECK(common::iequals("", ""));
			}
			SUBCASE("ascii") {
				SUBCASE("simple") {
					CHECK(common::iequals("abc", "ABC"));
					CHECK(common::iequals("ABC", "abc"));
					CHECK_FALSE(common::iequals("abc", "ABCD"));
					CHECK_FALSE(common::iequals("ABCD", "abc"));
				}
				SUBCASE("normal") {
					CHECK(common::iequals("this is a test", "This Is A Test"));
					CHECK_FALSE(common::iequals("this is a test", "This Is not A Test"));
				}
			}
			SUBCASE("wide-ish") {
				SUBCASE("simple") {
					CHECK(common::iequals(L"abc", L"ABC"));
					CHECK(common::iequals(L"ABC", L"abc"));
					CHECK_FALSE(common::iequals(L"abc", L"ABCD"));
					CHECK_FALSE(common::iequals(L"ABCD", L"abc"));
				}
				/*SUBCASE("other alphabets") {
					SUBCASE("Kana") {
						//Kana
						CHECK(common::iequals(L"ぁぃぅぇぉっゃゅょゎァィゥェォヵㇰヶㇱㇲッㇳㇴㇵㇶㇷㇷ゚ㇸㇹㇺャュョㇻㇼㇽㇾㇿヮ", L"あいうえおつやゆよわアイウエオカクケシスツトヌハヒフプヘホムヤユヨラリルレロワ") == true);
					}
					SUBCASE("Cyrillic") {
						//Cyrillic
						CHECK(common::iequals(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя", L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") == true);
					}
					SUBCASE("Greek") {
						//Greek
						CHECK(common::iequals(L"αβγδεζηθικλμνξοπρστυφχψω", L"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩ") == true);
					}
					SUBCASE("Armenian") {
						//Armenian
						CHECK(common::iequals(L"աբգդեզէըթժիլխծկհձղճմյնշոչպջռսվտրցւփքօֆ", L"ԱԲԳԴԵԶԷԸԹԺԻԼԽԾԿՀՁՂՃՄՅՆՇՈՉՊՋՌՍՎՏՐՑՒՓՔՕՖ") == true);
					}
					SUBCASE("Hebrew") {
						CHECK(common::iequals(L"אבגדהוזחטיכךלמנסעפצקרשת", L"abcdefghijklmnopqrstuvwx") == false);
					}
					SUBCASE("Arabic") {
						CHECK(common::iequals(L"غظضذخثتشرقصفعسنملكيطحزوهدجبأ", L"abcdefghijklmnopqrstuvwxyz012") == false);
					}
				}*/
			}
		}
	}
	TEST_CASE("trim") {
		std::vector<std::string> testset1 = { "test", "test test", "test\r\ntest", "test\ttest","test\vtest" };
		std::vector<std::string> testset2 = { "test\n", "test\r", "test\v", "test\r\n", "test ", "test \r\n\t\v\r" };
		std::vector<std::string> testset3 = { " test", "\vtest", "\ttest", "\rtest", "\ntest", "\r\ntest", "\r\n\t\v test" };
		std::vector<std::string> testset4 = { " test test ", "\t test test\r\n" };
		SUBCASE("ltrim") {
			SUBCASE("basic") {
				for (auto& i : testset1) {
					CAPTURE(i);
					CHECK_EQ(common::ltrim(i), i);
				}
				for (auto& i : testset2) {
					CAPTURE(i);
					CHECK_EQ(common::ltrim(i), i);
				}
				for (auto& i : testset3) {
					CAPTURE(i);
					CHECK_EQ(common::ltrim(i), "test");
				}
			}
		}
		SUBCASE("rtrim") {
			SUBCASE("basic") {
				for (auto& i : testset1) {
					CAPTURE(i);
					CHECK_EQ(common::rtrim(i), i);
				}
				for (auto& i : testset2) {
					CAPTURE(i);
					CHECK_EQ(common::rtrim(i), "test");
				}
				for (auto& i : testset3) {
					CAPTURE(i);
					CHECK_EQ(common::rtrim(i), i);
				}
			}
		}
		SUBCASE("trim") {
			SUBCASE("basic") {
				for (auto& i : testset1) {
					CAPTURE(i);
					CHECK_EQ(common::trim(i), i);
				}
				for (auto& i : testset2) {
					CAPTURE(i);
					CHECK_EQ(common::trim(i), "test");
				}
				for (auto& i : testset3) {
					CAPTURE(i);
					CHECK_EQ(common::trim(i), "test");
				}
				for (auto& i : testset4) {
					CAPTURE(i);
					CHECK_EQ(common::trim(i), "test test");
				}
			}
		}
	}
	TEST_CASE("erasenulls") {
		SUBCASE("basic") {
			CHECK_EQ(common::erasenulls(""), "");

			char test[10] = { 0 };
			test[0] = 't';
			test[1] = 'e';
			test[2] = 's';
			test[3] = 't';
			std::string t(test, 6);
			CHECK_EQ(common::erasenulls(t), "test");

			CHECK_EQ(common::erasenulls("test\t\r\n\0\0"), "test\t\r\n");
			//CHECK_EQ(common::erasenulls("\0\0te\0st\t\r\n\0\0"), "test\t\r\n");
			//CHECK_EQ(common::erasenulls("\0\0test\t\r\n\0\0"), "test\t\r\n");
			//CHECK_EQ(common::erasenulls("test\t\r\0\n\0\0"), "test\t\r\0\n");
		}
	}
	TEST_CASE("convert") {
		SUBCASE("empty") {
			CHECK_EQ(common::convert(L""), "");
		}
		SUBCASE("basic") {
			CHECK_EQ(common::convert(L"test"), "test");
			CHECK_EQ(common::convert(L"This is a simple test"), "This is a simple test");
		}
		SUBCASE("failures") {
			//CHECK_EQ(common::convert(L"ῆ𒀆𐨄エઐ᜗ﳒㆧ𐒎܇ꏫ獸𒐇Ꮯ쾴ឡﾙㄛዙଲꁠᝄ𒌮𝍝跗Ꮋޏㄨﱼ"), "ῆ𒀆𐨄エઐ᜗ﳒㆧ𐒎܇ꏫ獸𒐇Ꮯ쾴ឡﾙㄛዙଲꁠᝄ𒌮𝍝跗Ꮋޏㄨﱼ");
			//CHECK_EQ(common::convert(L"ᐃᔵᖊᏱᓈᒉᐚᘐᙋᏋᔂᑨᓺᒊ𐑂ᙽᏸ𐐘ᓄᏗᒷᒿᗕᓑᒯᘚᑢᗭᙹᔉᏨᏄᖇ"), "ᐃᔵᖊᏱᓈᒉᐚᘐᙋᏋᔂᑨᓺᒊ𐑂ᙽᏸ𐐘ᓄᏗᒷᒿᗕᓑᒯᘚᑢᗭᙹᔉᏨᏄᖇ");
			//CHECK_EQ(common::convert(L"ጬꖫዞꔳꔸⵐቶꘗꖅ߾ꕐ𐒚቎ⵎⵠ፫ⵘⷉߔ"), "ጬꖫዞꔳꔸⵐቶꘗꖅ߾ꕐ𐒚቎ⵎⵠ፫ⵘⷉߔ");
			//CHECK_EQ(common::convert(L"𒎀𐎯𒂞𐅢𒍙𒐟𐌽𒆗𒄋𒊉𒆒𐃆𒈾𒉟𐌎𒁪𐅭𐁾"), "𒎀𐎯𒂞𐅢𒍙𒐟𐌽𒆗𒄋𒊉𒆒𐃆𒈾𒉟𐌎𒁪𐅭𐁾");
			//CHECK_EQ(common::convert(L"ڇﴕݸﻃﲝﺛﹽؘﱦﰦﴬ﮷ﺭﶔؖﰦﭯﭖؙﴄﲣڃ؇ﲎﻱؙۧﰋﷻﷰﶤ﯄ݮﶢ٢"), "ڇﴕݸﻃﲝﺛﹽؘﱦﰦﴬ﮷ﺭﶔؖﰦﭯﭖؙﴄﲣڃ؇ﲎﻱؙۧﰋﷻﷰﶤ﯄ݮﶢ٢");
			//CHECK_EQ(common::convert(L"᠀ྏꡟᢣ𐨌ཛ࿌ཨᠸꡜ࿯࿈᢭ᡄᠳྲ꡷༲ཉ࿽གྔཱཱིཹ༏ᡠྲྨᢃᢁ"), "᠀ྏꡟᢣ𐨌ཛ࿌ཨᠸꡜ࿯࿈᢭ᡄᠳྲ꡷༲ཉ࿽གྔཱཱིཹ༏ᡠྲྨᢃᢁ");
			//CHECK_EQ(common::convert(L"ㄦㆸㄖㄡㆾㄇㄬㄫㄗㄔㆷㄝㆧ㄂ㆾㆿㄏㄈㄘㆵㄧㆦㄉㆢ"), "ㄦㆸㄖㄡㆾㄇㄬㄫㄗㄔㆷㄝㆧ㄂ㆾㆿㄏㄈㄘㆵㄧㆦㄉㆢ");
			//CHECK_EQ(common::convert(L"ƐႲӰⲰŋōꞺ֎ὈшⲪҼ῵ṔႯỺδẌ｠џ﬌ų"), "ƐႲӰⲰŋōꞺ֎ὈшⲪҼ῵ṔႯỺδẌ｠џ﬌ų");
			//CHECK_EQ(common::convert(L"梶鈽𦈏𥿆挂𧪖艌晙𧖜𦂷䒷𩐃𣍛𦵫𧗲𡌏"), "梶鈽𦈏𥿆挂𧪖艌晙𧖜𦂷䒷𩐃𣍛𦵫𧗲𡌏");
			//CHECK_EQ(common::convert(L"ﭏ֛׈וֹﬁק﬽רּקפ֬"), "ﭏ֛׈וֹﬁק﬽רּקפ֬");
			//CHECK_EQ(common::convert(L"୼෇઻ൎड़ೂ୛௭౓඼ᤔஓ੅કೱ૧ଉঀᱵে౗஭᥊"), "୼෇઻ൎड़ೂ୛௭౓඼ᤔஓ੅કೱ૧ଉঀᱵে౗஭᥊");
			//CHECK_EQ(common::convert(L"ㇿセㇷヘヾュﾔたぴチｧびモｬれｶﾙエㇸぉロごアﾊﾈや"), "ㇿセㇷヘヾュﾔたぴチｧびモｬれｶﾙエㇸぉロごアﾊﾈや");
			//CHECK_EQ(common::convert(L"ￜ덡뭈흹욞꼫큣위팟뎾섅놀셝똔홓뵦캈뙁능맼룴쪋긅훱"), "ￜ덡뭈흹욞꼫큣위팟뎾섅놀셝똔홓뵦캈뙁능맼룴쪋긅훱");
			//CHECK_EQ(common::convert(L"ދޢށܘ޿݉܋޵ޟ݌ިܻܸ܈ީ݀ݎܫޒܩ݀޴ܛܽޒސܤܳޮ݋܋ܱ"), "ދޢށܘ޿݉܋޵ޟ݌ިܻܸ܈ީ݀ݎܫޒܩ݀޴ܛܽޒސܤܳޮ݋܋ܱ");
			//CHECK_EQ(common::convert(L"𐑠𐑦𐑨𐑚𐑶𐑽𐑨𐑝𐑠𐑐"), "𐑠𐑦𐑨𐑚𐑶𐑽𐑨𐑝𐑠𐑐");
			//CHECK_EQ(common::convert(L"᜺ᝏᝍ᜽ᜃ᝖ᜍᝥᜰᝇᝂᜋᜒᝍᝦᜦ᝘ᜃᝒ᝿ᜅᜎᜅ᝘᝖ᝦᜌᝎᝣᝡᜱᝣ᜾᜾"), "᜺ᝏᝍ᜽ᜃ᝖ᜍᝥᜰᝇᝂᜋᜒᝍᝦᜦ᝘ᜃᝒ᝿ᜅᜎᜅ᝘᝖ᝦᜌᝎᝣᝡᜱᝣ᜾᜾");
			//CHECK_EQ(common::convert(L"႟ᮔนອ꥚ᥩ៺ႂฬ꨼ᭇ่ᦲ៻ᬌၹᦿ៍ᬶᥧ᦮ႆ᧍꥙ถ᭪หၪປ้฻"), "႟ᮔนອ꥚ᥩ៺ႂฬ꨼ᭇ่ᦲ៻ᬌၹᦿ៍ᬶᥧ᦮ႆ᧍꥙ถ᭪หၪປ้฻");
			//CHECK_EQ(common::convert(L"⋶⧞⚇⦍𝖺⢥⸖𝘲͑𝄐⧾𝈶┲⹲⟑✋⪹⃎㍸𝂡↶♂㌮⥖㋉"), "⋶⧞⚇⦍𝖺⢥⸖𝘲͑𝄐⧾𝈶┲⹲⟑✋⪹⃎㍸𝂡↶♂㌮⥖㋉");
			//CHECK_EQ(common::convert(L"ꌺꁮꁰꁩꀛꆒꌱꋖꉡꉈꂼꍤꉡꑆꍬ"), "ꌺꁮꁰꁩꀛꆒꌱꋖꉡꉈꂼꍤꉡꑆꍬ");
		}
	}
	TEST_CASE("readBuffer") {
		SUBCASE("basic") {			

			std::uniform_int_distribution<int> d(0, 255);
			unsigned char buffer[100] = { 0 };
			for (size_t i = 0; i < 100; i++) {
				buffer[i] = (char)(d(gen));
			}
			auto ans = common::readBuffer(buffer, 100);
			
			CHECK_GE(ans.capacity(), 100);
			CHECK_EQ(ans.size(), 100);

			for (size_t i = 0; i < 100; i++) {
				CHECK_EQ(ans[i], buffer[i]);
			}
		}
	}
	TEST_CASE("getFileSize") {
		
		//create file
		std::string file(tmpnam(NULL));
		std::ofstream fout;
		fout.open(file, std::ios::binary | std::ios::out);

		//fill file with random amount of random bytes
		std::uniform_int_distribution<size_t> d( 1, 2048);
		std::size_t fillSize = d(gen);
		
		std::uniform_int_distribution<int> d2(0, 255);
		for (std::size_t i = 0; i < fillSize; i++) {
			char a = (char)( d2(gen));
			fout.write(&a, 1);
		}
		//close file
		fout.close();


		auto size = common::getFileSize(file);
		CHECK_EQ(size, fillSize);

		//delete file
		remove(file.c_str());
	}
	TEST_CASE("readFile") {

		//create file
		std::string file(tmpnam(NULL));
		std::ofstream fout;
		fout.open(file, std::ios::binary | std::ios::out);

		//fill file with random amount of random bytes
		std::uniform_int_distribution<size_t> d(1, 2048);
		std::size_t fillSize = d(gen);

		std::uniform_int_distribution<int> d2(0, 255);
		unsigned char* buffer = new unsigned char[fillSize];

		for (std::size_t i = 0; i < fillSize; i++) {
			buffer[i] = (unsigned char)(d2(gen));					
		}		
		fout.write((char*)&buffer[0], fillSize);
		//close file
		fout.close();


		auto data = common::readFile(file, fillSize);

		CHECK_GE(data.capacity(), fillSize);
		CHECK_EQ(data.size(), fillSize);

		for (size_t i = 0; i < fillSize; i++) {
			CHECK_EQ(data[i], buffer[i]);
		}
		
		//delete file
		remove(file.c_str());
	}
	TEST_CASE("isbase64") {
		SUBCASE("basic") {
			CHECK(common::base64::is_base64('a'));
			CHECK(common::base64::is_base64('2'));
			CHECK(common::base64::is_base64('+'));
			CHECK(common::base64::is_base64('/'));
			CHECK_FALSE(common::base64::is_base64('\0'));
			CHECK_FALSE(common::base64::is_base64(' '));
			CHECK_FALSE(common::base64::is_base64('^'));
		}
	}
	TEST_CASE("base64_encode") {
		SUBCASE("basic") {
			CHECK_EQ(common::base64::base64_encode((unsigned char*)&"test", 4), "dGVzdA==");
			CHECK_EQ(common::base64::base64_encode((unsigned char*)&" ", 1), "IA==");
			CHECK_EQ(common::base64::base64_encode((unsigned char*)&"The quick brown fox jumped over the lazy dog.", 45), "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2cu");
			CHECK_EQ(common::base64::base64_encode((unsigned char*)&"<foo this)@$( test 0598ag", 25), "PGZvbyB0aGlzKUAkKCB0ZXN0IDA1OThhZw==");
		}
	}
	TEST_CASE("base64_decode") {
		SUBCASE("basic") {
			CHECK_EQ(common::base64::base64_decode("dGVzdA=="), "test");
			CHECK_EQ(common::base64::base64_decode("IA=="), " ");
			CHECK_EQ(common::base64::base64_decode("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgbGF6eSBkb2cu"), "The quick brown fox jumped over the lazy dog.");
			CHECK_EQ(common::base64::base64_decode("PGZvbyB0aGlzKUAkKCB0ZXN0IDA1OThhZw=="), "<foo this)@$( test 0598ag");
		}
	}
	TEST_CASE("ExtractBits") {
		SUBCASE("basic-1bit") {
			CHECK_EQ(common::ExtractBits(0xAA, 1, 0), 0);//since it is 1-based offset, the 0th bit does not exist
			CHECK_EQ(common::ExtractBits(0xAA, 1, 1), 0);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 2), 1);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 3), 0);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 4), 1);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 5), 0);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 6), 1);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 7), 0);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 8), 1);
			CHECK_EQ(common::ExtractBits(0xAA, 1, 9), 0);//since it is 1-based offset and an 8 bit input, the 9th bit does not exist
		}
		SUBCASE("basic-2bit") {
			CHECK_EQ(common::ExtractBits(0xBA, 2, 0), 0);//since it is 1-based offset, the 0th bit does not exist
			CHECK_EQ(common::ExtractBits(0xBA, 2, 1), 2);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 2), 1);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 3), 2);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 4), 3);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 5), 3);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 6), 1);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 7), 2);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 8), 1);
			CHECK_EQ(common::ExtractBits(0xBA, 2, 9), 0);//since it is 1-based offset and an 8 bit input, the 9th bit does not exist
		}
	}	
	TEST_CASE("VerifyGuids") {
		unsigned char test1[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
		unsigned char test2[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
		unsigned char test3[] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF };
		unsigned char test4[] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF };
		SUBCASE("basic") {
			CHECK(common::VerifyGuids(test3, test4));
			CHECK(common::VerifyGuids(test4, test3));
			CHECK_FALSE(common::VerifyGuids(test1, test2));
			CHECK_FALSE(common::VerifyGuids(test1, test3));
			CHECK_FALSE(common::VerifyGuids(test1, test4));
			CHECK_FALSE(common::VerifyGuids(test2, test1));
			CHECK_FALSE(common::VerifyGuids(test2, test3));
			CHECK_FALSE(common::VerifyGuids(test2, test4));			
			CHECK_FALSE(common::VerifyGuids(test3, test1));
			CHECK_FALSE(common::VerifyGuids(test3, test2));
			CHECK_FALSE(common::VerifyGuids(test4, test1));
			CHECK_FALSE(common::VerifyGuids(test4, test2));
		}
	}
	TEST_CASE("JsonEscape") {
		SUBCASE("basic") {
			CHECK_EQ(common::JsonEscape("test"), "test");
			CHECK_EQ(common::JsonEscape("\ttest\r\n"), "\\ttest\\r\\n");
			CHECK_EQ(common::JsonEscape("\"test\""), "\\\"test\\\"");
			CHECK_EQ(common::JsonEscape("foo¢bar"), "foo\\u00A2bar");
		}
	}
	TEST_CASE("helper.vector_join") {
		auto h = new common::helper();
		std::vector<char> t0{};
		std::vector<std::string> t1{ "one","two","three" };
		std::vector<int> t2{ 1,2,3,4 };
		
		SUBCASE("basic-string") {
			CHECK_EQ(h->vector_join(t1, "|", false), "one|two|three");
			CHECK_EQ(h->vector_join(t1, ",", true), "\"one\",\"two\",\"three\"");
		}
		SUBCASE("basic-int") {
			CHECK_EQ(h->vector_join(t2, "|", false), "1|2|3|4");
			CHECK_EQ(h->vector_join(t2, ",", true), "\"1\",\"2\",\"3\",\"4\"");
		}
		SUBCASE("empty") {
			CHECK_EQ(h->vector_join(t0, "|", false), "");
			CHECK_EQ(h->vector_join(t0, ",", true), "");
		}
	}


	TEST_CASE("ReadUShort") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadSShort") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadUInt") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadSInt") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadULong") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadULongLong") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadString") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadWString") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadFloat") {
		WARN("Not Implemented");
	}
	TEST_CASE("ReadDouble") {
		WARN("Not Implemented");
	}
}

