#pragma once
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "../common.hpp"


namespace Exec {

	class ExecExtensionInfo : public common::ExtensionInfo {
	public:
		std::string MachineType;
		std::string Subsystem;

		std::string LinkerVersion;
		std::string OsVersion;
		std::string ImageVersion;
		std::string SubsystemVersion;
		unsigned int Win32Version;
		std::vector<std::string> Characteristics;
		std::vector<std::string> DllCharacteristics;

		ExecExtensionInfo() : ExtensionInfo() {
			this->Extension = "exe";
			this->VersionName = "Executable";
			this->Win32Version = 0;
		};
		virtual std::string ToJson() {
			std::ostringstream str;
			str << "{";
			str << "\"extension\" : \"" << this->Extension << "\"";
			str << ", \"name\" : \"" << this->VersionName << "\"";
			if (this->MachineType.size() > 0) { str << ", \"machinetype\" : \"" << this->MachineType << "\""; }
			if (this->Subsystem.size() > 0) { str << ", \"subsystem\" : \"" << this->Subsystem << "\""; }
			if (this->LinkerVersion.size() > 0) { str << ", \"LinkerVersion\" : \"" << this->LinkerVersion << "\""; }
			if (this->OsVersion.size() > 0) { str << ", \"OsVersion\" : \"" << this->OsVersion << "\""; }
			if (this->ImageVersion.size() > 0) { str << ", \"ImageVersion\" : \"" << this->ImageVersion << "\""; }

			if (this->Characteristics.size() > 0) {
				str << ",\"Characteristics\": [";
				for (std::vector<std::string>::const_iterator i = this->Characteristics.begin(); i != this->Characteristics.end(); i++) {
					if (i != this->Characteristics.begin()) str << ",";
					str << "\"" << *i << "\"";
				}
				str << "]";
			}

			str << "}";
			return str.str();
		}
		virtual std::string ToXml() {
			std::ostringstream str;
			str << "<item>";
			str << "<extension>" << this->Extension << "</extension>";
			str << "<name>" << this->VersionName << "</name>";
			str << "<machinetype>" << this->MachineType << "</machinetype>";
			str << "<subsystem>" << this->Subsystem << "</subsystem>";
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() {
			std::ostringstream str;
			str << this->Extension << "\t" << this->Version << "\t" << this->VersionName;
			str << "\t" << this->Version;
			str << "\t" << this->MachineType;
			str << "\t" << this->Subsystem;
			return str.str();
		}
		virtual std::string ToCsv() {
			std::ostringstream str;
			str << this->Extension << "," << this->Version << "," << this->VersionName;
			str << "," << this->Version;
			str << "," << this->MachineType;
			str << "," << this->Subsystem;
			return str.str();
		}
	};

	typedef struct _IMAGE_DOS_HEADER {  // DOS .EXE header
		unsigned short MagicNumber;         // Magic number
		unsigned short BytesOnLastPage;     // Bytes on last page of file
		unsigned short PageCount;           // Pages in file
		unsigned short Relocations;         // Relocations
		unsigned short HeaderSizeParagraphs;// Size of header in paragraphs
		unsigned short MinExtraPara;			// Minimum extra paragraphs needed
		unsigned short MaxExtraPara;			// Maximum extra paragraphs needed
		unsigned short InitialSS;           // Initial (relative) SS value
		unsigned short InitialSP;           // Initial SP value
		unsigned short Checksum;				// Checksum
		unsigned short InitialIP;           // Initial IP value
		unsigned short InitialCS;           // Initial (relative) CS value
		unsigned short RelocationAddress;   // File address of relocation table
		unsigned short Overlay;					// Overlay number
		unsigned short Reserved[4];			// Reserved words
		unsigned short OEMIdentifier;       // OEM identifier
		unsigned short OEMInfo;					// OEM information
		unsigned short Reserved2[10];       // Reserved words
		unsigned int NewExeAddress;        // File address of new exe header
	} IMAGE_DOS_HEADER;


	typedef struct _COFF_FILE_HEADER {
		unsigned int Signature;
		unsigned short Machine;
		unsigned short NumberOfSections;
		unsigned int TimeDateStamp;
		unsigned int PointerToSymbolTable;
		unsigned int NumberOfSymbols;
		unsigned short SizeOfOptionalHeader;
		unsigned short Characteristics;
	} COFF_FILE_HEADER;

	std::map<unsigned int, std::string> CharacteristicsMap = {
		{0x0001,"Relocs Stripped"},
		{0x0002,"Executable Image"},
		{0x0004,"LINE_NUMS_STRIPPED"},
		{0x0008,"LOCAL_SYMS_STRIPPED"},
		{0x0010,"AGGRESSIVE_WS_TRIM"},
		{0x0020,"LARGE_ADDRESS_AWARE"},
		{0x0040,"REMOVABLE_RUN_FROM_SWAP"},
		{0x0080,"BYTES_REVERSED_LO"},
		{0x0100,"32BIT_MACHINE"},
		{0x0200,"DEBUG_STRIPPED"},
		{0x0400,"REMOVABLE_RUN_FROM_SWAP"},
		{0x0800,"NET_RUN_FROM_SWAP"},
		{0x1000,"SYSTEM"},
		{0x2000,"DLL"},
		{0x4000,"UP_SYSTEM_ONLY"},
		{0x8000,"BYTES_REVERSED_HI"}
	};
	std::map<unsigned int, std::string> DllCharacteristicsMap = {
		  {0x0040, "DYNAMIC_BASE"},
		  {0x0080, "FORCE_INTEGRITY"},
		  {0x0100, "NX_COMPAT"},
		  {0x0200, "NO_ISOLATION"},
		  {0x0400, "NO_SEH"},
		  {0x0800, "NO_BIND"},
		  {0x2000, "WDM_DRIVER"},
		  {0x8000, "TERMINAL_SERVER_AWARE"}
	};
	typedef struct _OPTIONAL_HEADER {
		unsigned short Magic;
		unsigned char MajorLinkerVersion;
		unsigned char MinorLinkerVersion;
		unsigned int SizeOfCode;
		unsigned int SizeOfInitializedData;
		unsigned int SizeOfUninitializedData;
		unsigned int AddressOfEntryPoint;
		unsigned int BaseOfCode;
		union {
			struct {
				unsigned int BaseOfData;
				unsigned int ImageBase;
			} pe32;
			unsigned long ImageBase_PE32p;
		} ImageBase;
		unsigned int SectionAlignment;
		unsigned int FileAlignment;
		unsigned short MajorOperatingSystemVersion;
		unsigned short MinorOperatingSystemVersion;
		unsigned short MajorImageVersion;
		unsigned short MinorImageVersion;
		unsigned short MajorSubsystemVersion;
		unsigned short MinorSubsystemVersion;
		unsigned int Win32VersionValue;
		unsigned int SizeOfImage;
		unsigned int SizeOfHeaders;
		unsigned int CheckSum;
		unsigned int Subsystem;
		unsigned int DllCharacteristics;
	} OPTIONAL_HEADER;

	std::string GetSubsystemString(unsigned int subsystem) {
		std::string ans;
		switch (subsystem) {
		case 0x0: ans = "Unknown Subsystem"; break;
		case 0x1: ans = "Device Driver"; break;
		case 0x2: ans = "Windows GUI"; break;
		case 0x3: ans = "Windows CUI"; break;
		case 0x7: ans = "Posix CUI"; break;
		case 0x9: ans = "Windows CE"; break;
		case 0x10: ans = "EFI Application"; break;
		case 0x11: ans = "EFI Service Driver"; break;
		case 0x12: ans = "EFI Runtime Driver"; break;
		case 0x13: ans = "EFI ROM Image"; break;
		case 0x14: ans = "XBOX"; break;
		}
		return ans;
	}

	std::string GetMachineTypeString(unsigned short machineType) {
		std::string ans;
		switch (machineType) {
		case 0x0: ans = "Unknown"; break;
		case 0x1d3: ans = "Matsushita AM33"; break;
		case 0x8664: ans = "x64"; break;
		case 0x1c0: ans = "ARM little endian"; break;
		case 0x1c4: ans = "ARMv7 (or higher) Thumb mode only"; break;
		case 0xaa64: ans = "ARMv8 in 64-bit mode"; break;
		case 0xebc: ans = "EFI byte code"; break;
		case 0x14c: ans = "Intel 386"; break;
		case 0x200: ans = "Intel Itanium"; break;
		case 0x9041: ans = "Mistubishi MR32R little endian"; break;
		case 0x266: ans = "MIPS16"; break;
		case 0x366: ans = "MIPS with FPU"; break;
		case 0x466: ans = "MIPS16 with FPU"; break;
		case 0x1f0: ans = "Power PC little endian"; break;
		case 0x1f1: ans = "Power PC with floating point support"; break;
		case 0x166: ans = "MIPS little endian"; break;
		case 0x1a2: ans = "Hitachi SH3"; break;
		case 0x1a3: ans = "Hitachi SH3 DSP"; break;
		case 0x1a6: ans = "Hitachi SH4"; break;
		case 0x1a8: ans = "Hitachi SH5"; break;
		case 0x1c2: ans = "ARM or Thumb (interworking)"; break;
		case 0x169: ans = "MIPS little-endian WCE v2"; break;
		}
		return ans;
	}

	std::vector<std::string> BuildVectorFromMap(std::map<unsigned int, std::string> map, unsigned int key) {
		std::vector<std::string> ans;
		for (std::map<unsigned int, std::string>::iterator i = map.begin(); i != map.end(); i++) {
			if (i->first & key)
				ans.push_back(i->second);
		}
		return ans;
	}
	bool checkContains(std::vector<std::string> v, std::string item) {
		return std::find(v.begin(), v.end(), item) != v.end();
	}

	std::string BuildVersionString(unsigned short major, unsigned short minor) {
		std::string ans;
		ans += std::to_string(static_cast<unsigned long long>(major));
		ans += ".";
		ans += std::to_string(static_cast<unsigned long long>(minor));
		return ans;
	}

	std::vector<common::ExtensionInfo*> Detailer(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		ExecExtensionInfo* info = new ExecExtensionInfo();

		std::vector<unsigned char> buf2 = common::readFile(file, 2048);

		IMAGE_DOS_HEADER* dosHeader = new IMAGE_DOS_HEADER();
		std::memcpy(dosHeader, &buf2[0], sizeof(IMAGE_DOS_HEADER));
		
		unsigned int peHeaderStart = dosHeader->NewExeAddress;


		unsigned int totalSizeNeeded = peHeaderStart + sizeof(COFF_FILE_HEADER) + sizeof(OPTIONAL_HEADER);
		if (buf2.size() < totalSizeNeeded) {
			buf2 = common::readFile(file, totalSizeNeeded);
		}

		if (dosHeader->NewExeAddress + sizeof(COFF_FILE_HEADER) < buf2.size() ) {
			COFF_FILE_HEADER* coffHeader = new COFF_FILE_HEADER();
			std::memcpy(coffHeader, &buf2[peHeaderStart], sizeof(COFF_FILE_HEADER));

			info->MachineType = GetMachineTypeString(coffHeader->Machine);
			info->Characteristics = BuildVectorFromMap(CharacteristicsMap, coffHeader->Characteristics);
			if (coffHeader->Characteristics & 0x2000) {
				info->Extension = "dll";
				info->VersionName = "Dynamic Link Library";
			}
			if (coffHeader->Characteristics & 0x1000) {
				info->Extension = "sys";
				info->VersionName = "Kernal Mode Executable";
			}

		
			if (peHeaderStart + sizeof(COFF_FILE_HEADER) + sizeof(OPTIONAL_HEADER) < buf2.size()) {
				OPTIONAL_HEADER* optHeader = new OPTIONAL_HEADER;
				std::memcpy(optHeader, &buf2[peHeaderStart + sizeof(COFF_FILE_HEADER)], sizeof(OPTIONAL_HEADER));


				info->Subsystem = GetSubsystemString(optHeader->Subsystem);
				info->LinkerVersion = BuildVersionString(optHeader->MajorLinkerVersion, optHeader->MinorLinkerVersion);
				info->OsVersion = BuildVersionString(optHeader->MajorOperatingSystemVersion, optHeader->MinorOperatingSystemVersion);
				info->ImageVersion = BuildVersionString(optHeader->MajorImageVersion, optHeader->MinorImageVersion);
				info->SubsystemVersion = BuildVersionString(optHeader->MajorSubsystemVersion, optHeader->MinorSubsystemVersion);
				info->Win32Version = optHeader->Win32VersionValue;
				info->DllCharacteristics = BuildVectorFromMap(DllCharacteristicsMap, optHeader->DllCharacteristics);
			
				delete optHeader;
			}

			delete coffHeader;
		}
		delete dosHeader;

		ans.push_back(info);
		return ans;
	}
}