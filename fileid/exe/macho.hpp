#pragma once
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "../common.hpp"

namespace Exec {
	namespace MachO {
		class MachOExtensionInfo : public common::ExtensionInfo {
		public:
			std::string CpuType;
			std::string CpuSubType;
			std::string FileType;
			unsigned int NumberLoadCommands;
			unsigned int SizeLoadCommands;
			std::string Flags;

			MachOExtensionInfo() : ExtensionInfo() {
				this->Extension = "o";
				this->NumberLoadCommands = 0;
				this->SizeLoadCommands = 0;
			}
			virtual std::string ToJson() const override {
				std::ostringstream str;
				str << "{";
				str << "\"extension\" : \"" << this->Extension << "\"";
				str << ", \"name\" : \"" << this->VersionName << "\"";
				if (this->CpuType.size() > 0) { str << ", \"CpuType\" : \"" << this->CpuType << "\""; }
				if (this->CpuSubType.size() > 0) { str << ", \"CpuSubType\" : \"" << this->CpuSubType << "\""; }
				if (this->FileType.size() > 0) { str << ", \"FileType\" : \"" << this->FileType << "\""; }
				str << ", \"NumberLoadCommands\" : \"" << this->NumberLoadCommands << "\""; 
				str << ", \"SizeLoadCommands\" : \"" << this->SizeLoadCommands << "\"";
				if (this->Flags.size() > 0) { str << ", \"Flags\" : \"" << this->Flags << "\""; }

				str << "}";
				return str.str();
			}
			virtual std::string ToXml() const override {
				std::ostringstream str;
				str << "<item>";
				str << this->buildBaseXml();
				if (this->CpuType.size() > 0) { str << "<CpuType>" << this->CpuType << "</CpuType>"; }
				if (this->CpuSubType.size() > 0) { str << "<CpuSubType>" << this->CpuSubType << "</CpuSubType>"; }
				if (this->FileType.size() > 0) { str << "<FileType>" << this->FileType << "</FileType>"; }
				str << "<NumberLoadCommands>" << this->NumberLoadCommands << "</NumberLoadCommands>";
				str << "<SizeLoadCommands>" << this->SizeLoadCommands << "</SizeLoadCommands>";
				if (this->Flags.size() > 0) { str << "<Flags>" << this->Flags << "</Flags>"; }
				str << "</item>";
				return str.str();
			}
			virtual std::string ToText() const override {
				std::ostringstream str;
				str << this->Extension;
				str << "\t" << this->VersionName;
				return str.str();
			}
			virtual std::string ToCsv() const override {
				std::ostringstream str;
				str << this->Extension;
				str << "," << this->VersionName;
				return str.str();
			}
		};

		struct mach_header {
			unsigned int magic;
			unsigned int cputype;
			unsigned int cpusubtype;
			unsigned int filetype;
			unsigned int numloadcommands;
			unsigned int sizeloadcommands;
			unsigned int flags;
		};

		std::string cpuType2String(unsigned int cputype) {
			std::string ans;
			switch (cputype) {
			case 1: ans = "VAX"; break;
			case 2: ans = "ROMP"; break;
			case 4: ans = "NS32032"; break;
			case 5: ans = "NS32332"; break;
			case 6: ans = "MC680x0"; break;
			case 7: ans = "I386"; break;
			case 8: ans = "MIPS"; break;
			case 9: ans = "NS32532"; break;
			case 11: ans = "HPPA"; break;
			case 12: ans = "ARM"; break;
			case 13: ans = "MC88000"; break;
			case 14: ans = "SPARC"; break;
			case 15: ans = "I860"; break;
			case 16: ans = "I860_LITTLE"; break;
			case 17: ans = "RS6000"; break;
			case 18: ans = "POWERPC"; break;
			case 0x1000000: ans = "ARCH_ABI64"; break;
			case 0x1000007: ans = "X86_64"; break;
			case 0x1000012: ans = "POWERPC64"; break;
			case 255: ans = "VEO"; break;
			case 0xffffffff: ans = "ANY"; break;
			}
			return ans;

		}
		std::string cpuSubType2String(unsigned int cputype, unsigned int cpusubtype) {
			std::string ans = "UNKNOWN";
			switch (cputype) {
			case 1: //VAX
				switch (cpusubtype) {
				case 0: ans = "VAX_ALL"; break;
				case 1: ans = "VAX780"; break;
				case 2: ans = "VAX785"; break;
				case 3: ans = "VAX750"; break;
				case 4: ans = "VAX730"; break;
				case 5: ans = "UVAXI"; break;
				case 6: ans = "UVAXII"; break;
				case 7: ans = "VAX8200"; break;
				case 8: ans = "VAX8500"; break;
				case 9: ans = "VAX8600"; break;
				case 10: ans = "VAX8650"; break;
				case 11: ans = "VAX8800"; break;
				case 12: ans = "UVAXIII"; break;				
				}
				break;
			case 2: //ROMP
				switch (cpusubtype) {
				case 0: ans = "RT_ALL"; break;
				case 1: ans = "RT_PC"; break;
				case 2: ans = "RT_APC"; break;
				case 3: ans = "RT_135"; break;
				}
				break;
			case 4: //NS32032
			case 5: //NS32332
			case 9: //NS23532
				switch (cpusubtype) {
				case 0: ans = "MMAX_ALL"; break;
				case 1: ans = "MMAX_DPC (032 CPU)"; break;
				case 2: ans = "SQT"; break;
				case 3: ans = "MMAX_APC_FPU (32081 FPU)"; break;
				case 4: ans = "MMAX_APC_FPA (Weitek FPA)"; break;
				case 5: ans = "MMAX_XPC (532 CPU)"; break;
				}
				break;
			case 6: //MC680x0";
				switch (cpusubtype) {
				case 1: ans = "MC680x0_ALL"; break;
				case 2: ans = "MC68040"; break;
				case 3: ans = "MC68030_ONLY"; break;
				}
				break;
			case 7: //I386";
				switch (cpusubtype) {
				case 0: ans = "INTEL_ALL"; break;
				case 3: ans = "I386_ALL"; break;
				case 4: ans = "INTEL_486"; break;
				case 5: ans = "INTEL_586"; break;
				case 8: ans = "PENTIUM_3"; break;
				case 9: ans = "PENTIUM_M"; break;
				case 10: ans = "PENTIUM_4"; break;
				case 11: ans = "ITANIUM"; break;
				case 12: ans = "XEON"; break;
				case 34: ans = "XEON_MP"; break;
				case 42: ans = "PENTIUM_4_M"; break;
				case 43: ans = "ITANIUM_2"; break;
				case 38: ans = "PENTPRO"; break;
				case 40: ans = "PENTIUM_3_M"; break;
				case 52: ans = "PENTIUM_3_XEON"; break;
				case 102: ans = "PENTII_M3"; break;
				case 132: ans = "INTEL_486SX"; break;
				case 166: ans = "PENTII_M5"; break;
				case 199: ans = "CELERON"; break;
				case 231: ans = "CELERON_MOBILE"; break;
				}
				break;
			case 8: //MIPS";
				switch (cpusubtype) {
				case 0: ans = "MIPS_ALL"; break;
				case 1: ans = "MIPS_R2300"; break;
				case 2: ans = "MIPS_R2600"; break;
				case 3: ans = "MIPS_R2800"; break;
				case 4: ans = "MIPS_R2000a"; break;
				case 5: ans = "MIPS_R2000"; break;
				case 6: ans = "MIPS_R3000a"; break;
				case 7: ans = "MIPS_R3000"; break;
				}
				break;
			case 11: //HPPA";
				switch (cpusubtype) {
				case 0: ans = "HPPA_7100"; break;
				case 1: ans = "HPPA_7100LC"; break;
				}
				break;
			case 12: //ARM";
				switch (cpusubtype) {
				case 0: ans = "ARM_ALL12"; break;
				case 5: ans = "ARM_V4T"; break;
				case 6: ans = "ARM_V6"; break;
				case 7: ans = "ARM_V5TEJ"; break;
				case 8: ans = "ARM_XSCALE"; break;
				case 9: ans = "ARM_V7"; break;
				case 10: ans = "ARM_V7F"; break;
				case 12: ans = "ARM_V7K"; break;
				}
				break;
			case 13: //MC88000";
				switch (cpusubtype) {

				}
				break;
			case 14: //SPARC";
				switch (cpusubtype) {
				case 0: ans = "SPARC_ALL"; break;
				}
				break;
			case 15: //I860";
				switch (cpusubtype) {
				case 0: ans = "I860_ALL"; break;
				case 1: ans = "I860_860"; break;
				}
				break;
			case 16: //I860_LITTLE";
				switch (cpusubtype) {

				}
				break;
			case 17: //RS6000";
				switch (cpusubtype) {

				}
				break;
			case 18: //POWERPC";
				switch (cpusubtype) {
				case 0: ans = "POWERPC_ALL"; break;
				case 1: ans = "POWERPC_601"; break;
				case 2: ans = "POWERPC_602"; break;
				case 3: ans = "POWERPC_603"; break;
				case 4: ans = "POWERPC_603e"; break;
				case 5: ans = "POWERPC_603ev"; break;
				case 6: ans = "POWERPC_604"; break;
				case 7: ans = "POWERPC_604e"; break;
				case 8: ans = "POWERPC_620"; break;
				case 9: ans = "POWERPC_750"; break;
				case 10: ans = "POWERPC_7400"; break;
				case 11: ans = "POWERPC_7450"; break;
				case 100: ans = "POWERPC_970"; break;
				}
				break;
			case 0x1000000: //ARCH_ABI64";
				switch (cpusubtype) {

				}
				break;
			case 0x1000007: //X86_64";
				switch (cpusubtype) {
				case 3: ans = "X86_64_ALL"; break;
				case 4: ans = "X86_ARCH1"; break;
				}
				break;
			case 0x1000012: //POWERPC64";
				switch (cpusubtype) {

				}
				break;
			case 255: //VEO";
				switch (cpusubtype) {

				}
				break;
			case 0xffffffff: //ANY";
				switch (cpusubtype) {

				}
				break;
			}

			if (ans == "UNKNOWN") {
				ans += " (" + common::int_to_hex(cpusubtype) + ")";
			}

			return ans;
		}
		std::string filetype2String(unsigned int filetype) {
			std::string ans;
			switch (filetype) {

			}
			return ans;
		}
		std::string flags2String(unsigned int flags) {
			std::string ans;
			return ans;
		}

		std::vector<common::ExtensionInfo*> Detailer(const std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;
			MachOExtensionInfo* info = new MachOExtensionInfo();

			std::vector<unsigned char> buf2 = common::readFile(file, 2048);

			mach_header* header = new mach_header();
			std::memcpy(header, &buf2[0], sizeof(mach_header));

			info->VersionName = common::int_to_hex(header->magic);
			info->Version = header->magic;
			info->CpuType = cpuType2String(header->cputype);
			info->CpuSubType = cpuSubType2String(header->cputype, header->cpusubtype);
				info->FileType = filetype2String(header->filetype);
			info->NumberLoadCommands = header->numloadcommands;
			info->SizeLoadCommands = header->sizeloadcommands;
			info->Flags = flags2String(header->flags);

			delete header;
			ans.push_back(info);
			return ans;
		}


	}
}