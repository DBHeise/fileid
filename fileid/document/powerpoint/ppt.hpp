#pragma once
#include <string>
#include <vector>
#include "../../common.hpp"
#include "../../oless/OleCommon.hpp"

namespace document {
	namespace powerpoint {

		static const char PP95SIG[] = "Microsoft (R) PowerPoint (R) Windows  "; //38
		struct RecordHeader {
			unsigned short recVer : 4;
			unsigned short recInstance : 12;
			unsigned short recType : 2;
			unsigned long recLen;
		};
		struct PointStruct {
			unsigned long x;
			unsigned long y;
		};
		struct RatioStruct {
			unsigned long numer;
			unsigned long denom;
		};
		struct DocumentAtom {
			RecordHeader rh;
			PointStruct slideSize;
			PointStruct notesSize;
			RatioStruct serverZoom;
			unsigned long notesMasterPersistIdRef;
			unsigned long handoutMasterPersistIdRef;
			unsigned short firstSlideNumber;
			unsigned short slideSizeType;
			unsigned char fSaveWithFonts;
			unsigned char fOmitTitlePlace;
			unsigned char fRightToLeft;
			unsigned char fShowComments;
		};
		struct DocContainer {
			RecordHeader rh;
			DocumentAtom documentAtom;
		};

		struct CurrentUserAtom {
			RecordHeader rh;
			unsigned long size;
			unsigned long headerToken;
			unsigned long offsetToCurrentEdit;
			unsigned short lenUserName;
			unsigned short docFileVersion;
			unsigned char majorVersion;
			unsigned char minorVersion;
			unsigned short build;
		};
		struct UserEditAtom {
			RecordHeader rh;
			unsigned long lastSlideIdRef;
			unsigned short version;
			unsigned char minorVersion;
			unsigned char majorVersion;
			unsigned long offsetLastEdit;
			unsigned long offsetPersistDirectory;
			unsigned long docPersistIdRef;
			unsigned long persistIdSeed;
			unsigned short lastView;
			unsigned short unused;
		};

		bool withinCheck(unsigned long num, unsigned long target, unsigned long range) {
			return (num >= (target - range) && num <= (target + range));
		}
		//Powerpoint (.ppt) specific
		unsigned short GetPptVersion(const POLE::Storage* storage, const std::vector<uint8_t> stream) {
			unsigned short version = 0;
						
			auto currentUserStream = oless::ReadStream(const_cast<POLE::Storage*>(storage), L"/Current User");
			auto bufferCurrentUser = currentUserStream.data();
			auto maxCurrentUser = currentUserStream.size();
			if (sizeof(CurrentUserAtom) > maxCurrentUser) {
				return -1;
			}

			CurrentUserAtom* cua = (CurrentUserAtom*)bufferCurrentUser;

			auto buffer = stream.data();
			auto max = stream.size();
			unsigned int index = cua->offsetToCurrentEdit;

			if (index + sizeof(UserEditAtom) > max) {
				return -1;
			}

			UserEditAtom* uea = (UserEditAtom*)&buffer[index];
			version = uea->version;

			return version;
		}

		std::string GetVersion_Powerpoint(unsigned short version) {
			std::string ans = "Unknown";

			if (version == 0) {
				ans = "Non-Office";
			}
			else if (withinCheck(version, 4569, 10)) {
				ans = "Office 2013 SP1";
			}
			else if (withinCheck(version, 4569, 10)) {
				ans = "Office 2013 SP1";
			}
			else if (withinCheck(version, 4420, 10)) {
				ans = "Office 2013 RTM";
			}
			else if (withinCheck(version, 4128, 10)) {
				ans = "Office 2013 Preview";
			}
			else if (withinCheck(version, 7015, 10)) {
				ans = "Office 2010 SP2"; 	//14.0.7015.1000
			}
			else if (withinCheck(version, 6029, 10)) {
				ans = "Office 2010 SP1"; 	//14.0.6029.1000
			}
			else if (withinCheck(version, 4763, 10)) {
				ans = "Office 2010 RTM"; 	//14.0.4763.1000
			}
			else if (withinCheck(version, 6425, 10)) {
				ans = "Office 2007 SP2";    //12.0.6425.1000
			}
			else if (withinCheck(version, 6211, 10)) {
				ans = "Office 2007 SP1";    //12.0.6211.1000
			}
			else if (withinCheck(version, 4518, 10)) {
				ans = "Office 2007 RTM";    //12.0.6425.1014

			}
			else if (withinCheck(version, 8173, 10)) {
				ans = "Office 2003 SP3"; 	// 11.0.8169.?
			}
			else if (withinCheck(version, 7969, 10)) {
				ans = "Office 2003 SP2"; 	// 11.0.6564.6568
			}
			else if (withinCheck(version, 6361, 10)) {
				ans = "Office 2003 SP1"; 	// 11.0.6361.0
			}
			else if (withinCheck(version, 5529, 10)) {
				ans = "Office 2003 RTM"; 	// 11.0.5529.0
			}
			else if (withinCheck(version, 6501, 10)) {
				ans = "Office XP SP3"; 		// 10.0.6501.6735
			}
			else if (withinCheck(version, 4205, 10)) {
				ans = "Office XP SP2"; 		// 10.0.4205.0
			}
			else if (withinCheck(version, 3506, 10)) {
				ans = "Office XP SP1"; 		// 10.0.3506.0
			}
			else if (withinCheck(version, 2623, 10)) {
				ans = "Office XP RTM"; 		// 10.0.2623.0
			}
			else if (withinCheck(version, 6620, 10)) {
				ans = "Office 2000 SP3"; 	// 9.0.6620
			}
			else if (withinCheck(version, 4527, 10)) {
				ans = "Office 2000 SP2"; 	// 9.0.4527
			}
			else if (withinCheck(version, 3821, 10)) {
				ans = "Office 2000 SP1"; 	// 9.0.3821
			}
			else if (withinCheck(version, 2716, 10)) {
				ans = "Office 2000 RTM"; 	// 9.0.2716
			}
			else if (withinCheck(version, 3516, 10)) {
				ans = "Office 97 RTM"; 		// 8.0.3516
			}
			else if (withinCheck(version, 4208, 10)) {
				ans = "Office 97 SR1"; 		// 8.0.4208
			}
			else if (withinCheck(version, 5507, 10)) {
				ans = "Office 97 SR2"; 		// 8.0.5507
			}
			return ans;
		}

		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			e->Version = GetPptVersion(storage, stream);
			e->VersionName = GetVersion_Powerpoint(e->Version);
		}

	}
}