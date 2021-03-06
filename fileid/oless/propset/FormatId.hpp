#pragma once
#include "../../common.hpp"

namespace oless {
	namespace propset {
		enum class FormatId {
			FMTID_Unknown,
			FMTID_SummaryInformation,
			FMTID_DocSummaryInformation,
			FMTID_UserDefiniedProperties
		};
		const unsigned char guid_SummaryInformation[16] = { 0xE0,0x85,0x9F,0xF2,0xF9,0x4F,0x68,0x10,0xAB,0x91,0x08,0x00,0x2B,0x27,0xB3,0xD9 }; //F29F85E0-4FF9-1068-AB91-08002B27B3D9
		const unsigned char guid_DocumentSummaryInformation[16] = { 0x02,0xD5,0xCD,0xD5,0x9C,0x2E,0x1B,0x10,0x93,0x97,0x08,0x00,0x2B,0x2C,0xF9,0xAE }; //D5CDD502-2E9C-101B-9397-08002B2CF9AE
		const unsigned char guid_UserDefinedProperties[16] = { 0x05,0xD5,0xCD,0xD5,0x9C,0x2E,0x1B,0x10,0x93,0x97,0x08,0x00,0x2B,0x2C,0xF9,0xAE }; //D5CDD505-2E9C-101B-9397-08002B2CF9AE
		const unsigned char guid_DiscardableInformation[16] = { 0xB0,0xEB,0x25,0xD7,0xB8,0xC9,0xD1,0x11,0x89,0xBC,0x00,0x00,0xF8,0x04,0xB0,0x57 }; //d725ebb0-c9b8-11d1-89bc-0000f804b057
		const unsigned char guid_ImageSummaryInformation[16] = { 0x8F,0x04,0x44,0x64,0x8B,0x4C,0xD1,0x11,0x8B,0x70,0x08,0x00,0x36,0xB1,0x1A,0x03 }; //6444048f-4c8b-11d1-8b70-080036b11a03
		const unsigned char guid_AudioSummaryInformation[16] = { 0x90,0x04,0x44,0x64,0x8B,0x4C,0xD1,0x11,0x8B,0x70,0x08,0x00,0x36,0xB1,0x1A,0x03 }; //64440490-4C8B-11D1-8B70-080036B11A03
		const unsigned char guid_VideoSummaryInformation[16] = { 0x91,0x04,0x44,0x64,0x8B,0x4C,0xD1,0x11,0x8B,0x70,0x08,0x00,0x36,0xB1,0x1A,0x03 }; //64440491-4C8B-11D1-8B70-080036B11A03
		const unsigned char guid_MediaFileSummaryInformation[16] = { 0x92,0x04,0x44,0x64,0x8B,0x4C,0xD1,0x11,0x8B,0x70,0x08,0x00,0x36,0xB1,0x1A,0x03 }; //64440492-4c8b-11d1-8b70-080036b11a03
		const unsigned char guid_Intshcut[16] = { 0xA0,0x14,0x02,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46 }; //000214A0-0000-C000-0000-000000000046
		const unsigned char guid_InternetSite[16] = { 0xA1,0x14,0x02,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46 }; //000214A1-0000-C000-0000-000000000046
		const unsigned char guid_ShellDetails[16] = { 0xA6,0x6A,0x63,0x28,0x3D,0x95,0xD2,0x11,0xB5,0xD6,0x00,0xC0,0x4F,0xD9,0x18,0xD0 }; //28636aa6-953d-11d2-b5d6-00c04fd918d0
		const unsigned char guid_Storage[16] = { 0x30,0xF1,0x25,0xB7,0xEF,0x47,0x1A,0x10,0xA5,0xF1,0x02,0x60,0x8C,0x9E,0xEB,0xAC }; //b725f130-47ef-101a-a5f1-02608c9eebac
		const unsigned char guid_ImageProperties[16] = { 0xA1,0x1D,0xB8,0x14,0x35,0x01,0x31,0x4D,0x96,0xD9,0x6C,0xBF,0xC9,0x67,0x1A,0x99 }; //14b81da1-0135-4d31-96d9-6cbfc9671a99
		const unsigned char guid_CustomImageProperties[16] = { 0x0E,0x8B,0xCD,0x7E,0x36,0xC1,0x9B,0x4A,0x94,0x11,0x4E,0xBD,0x66,0x73,0xCC,0xC3 }; //7ECD8B0E-C136-4a9b-9411-4EBD6673CCC3
		const unsigned char guid_LibraryProperties[16] = { 0x7F,0xB6,0x76,0x5D,0x3D,0x9B,0xBB,0x44,0xB6,0xAE,0x25,0xDA,0x4F,0x63,0x8A,0x67 }; //5d76b67f-9b3d-44bb-b6ae-25da4f638a67
		const unsigned char guid_Displaced[16] = { 0x33,0x4B,0x17,0x9B,0xFF,0x40,0xD2,0x11,0xA2,0x7E,0x00,0xC0,0x4F,0xC3,0x08,0x71 }; //9B174B33-40FF-11d2-A27E-00C04FC30871
		const unsigned char guid_Briefcase[16] = { 0x21,0x8B,0x8D,0x32,0x29,0x77,0xFC,0x4B,0x95,0x4C,0x90,0x2B,0x32,0x9D,0x56,0xB0 }; //328D8B21-7729-4bfc-954C-902B329D56B0
		const unsigned char guid_Misc[16] = { 0x34,0x4B,0x17,0x9B,0xFF,0x40,0xD2,0x11,0xA2,0x7E,0x00,0xC0,0x4F,0xC3,0x08,0x71 }; //9B174B34-40FF-11d2-A27E-00C04FC30871
		const unsigned char guid_Music[16] = { 0x2E,0x37,0xA3,0x56,0x9C,0xCE,0xD2,0x11,0x9F,0x0E,0x00,0x60,0x97,0xC6,0x86,0xF6 }; //56A3372E-CE9C-11d2-9F0E-006097C686F6
		const unsigned char guid_Volume[16] = { 0x35,0x4B,0x17,0x9B,0xFF,0x40,0xD2,0x11,0xA2,0x7E,0x00,0xC0,0x4F,0xC3,0x08,0x71 }; //9B174B35-40FF-11d2-A27E-00C04FC30871
		const unsigned char guid_DRM[16] = { 0xE4,0x19,0xAC,0xAE,0xAE,0x89,0x08,0x45,0xB9,0xB7,0xBB,0x86,0x7A,0xBE,0xE2,0xED }; //AEAC19E4-89AE-4508-B9B7-BB867ABEE2ED
		const unsigned char guid_WebView[16] = { 0x80,0x54,0x27,0xF2,0x82,0xF7,0x91,0x42,0xBD,0x94,0xF1,0x36,0x93,0x51,0x3A,0xEC }; //F2275480-F782-4291-BD94-F13693513AEC
		const unsigned char guid_Query[16] = { 0x90,0x1C,0x69,0x49,0x17,0x7E,0x1A,0x10,0xA9,0x1C,0x08,0x00,0x2B,0x2E,0xCD,0xA9 }; //49691c90-7e17-101a-a91c-08002b2ecda9


		FormatId FormatIdFromGuid(unsigned char guid[16]) {

			if (common::VerifyGuids(guid, guid_SummaryInformation)) {
				return FormatId::FMTID_SummaryInformation;
			}
			else if (common::VerifyGuids(guid, guid_DocumentSummaryInformation)) {
				return FormatId::FMTID_DocSummaryInformation;
			}
			else if (common::VerifyGuids(guid, guid_UserDefinedProperties)) {
				return FormatId::FMTID_UserDefiniedProperties;
			}
			return FormatId::FMTID_Unknown;
		}

	}
}