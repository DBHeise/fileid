#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"
#include "../../oless/OleCommon.hpp"

namespace document {
	namespace word {


		struct FibBase {
			unsigned short wIdent; // 2 bytes
			unsigned short nFib;
			unsigned short unused1;
			unsigned short lid;
			unsigned short pnNext;
			unsigned short flags;
			unsigned short nFibBack; //must be 0x000BF or 0x00C1
			unsigned char lKey[4];
			short flags2;
			char reserved[12];
		};

		struct FibRgW97 {
			char buffer[28];
		};

		struct FibRgLw97 {
			char buffer[88];
		};

		struct Fib {
			FibBase base;
			unsigned short csw;
			FibRgW97 fibRgW;
			unsigned short cslw;
			FibRgLw97 fibRgLw;
			unsigned short cbRgFcLcb;
		};

		struct Fib2 {
			unsigned short cswNew;
			unsigned short nFibNew;
		};

		//Word (.doc) specific
		unsigned short GetnFib(std::vector<uint8_t> stream) {
			unsigned short nFib = 0;
			auto buffer = stream.data();
			auto max = stream.size();
			unsigned int index = 0;

			if (sizeof(Fib) > max) {
				return -1;
			}
			Fib* fib = (Fib*)buffer;
			nFib = fib->base.nFib;

			if (fib->cbRgFcLcb > 0x00FF) {
				//Corrupted file
				return nFib;
			}
			
			index = sizeof(Fib) + (fib->cbRgFcLcb * 8);
			
			if (index + sizeof(Fib2) > max) {
				return nFib;
			}
			Fib2* fib2 = (Fib2*)&buffer[index];
				
			if (fib2->cswNew != 0) {
				nFib = fib2->nFibNew;
			}
			return nFib;
		}
		std::string GetVersion_Word(unsigned short version) {
			std::string ans;

			switch (version) {
			case 314: ans = "Word2005"; break;
			case 274: ans = "Word2005_Compat2003"; break;
			case 268: ans = "Word2003"; break;
			case 257: ans = "Word2002"; break;
			case 217: ans = "Word2000"; break;
			case 193: ans = "Word97"; break;
			case 104: ans = "Word95_Or_Word6"; break;
			case 105: ans = "Word95Beta"; break;
			case 101: ans = "WinWord6.0"; break;
			case 45:  ans = "WinWord2.0"; break;
			case 33:  ans = "WinWord1.0"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}
		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			e->Version = GetnFib(stream);
			e->VersionName = GetVersion_Word(e->Version);
		}

	}
}