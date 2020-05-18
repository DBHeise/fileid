#pragma once
#include <string>
#include <vector>
#include <map>
#include "../../common.hpp"

namespace media {
	namespace mp4 {
		class Mp4ExtensionInfo : public common::ExtensionInfo {
		public:
			unsigned int Version;
			std::string Brand;
			std::string BrandCode;

			Mp4ExtensionInfo() : ExtensionInfo() {
				this->Extension = "mp4";
				this->VersionName = "MPEG-4 Media File";
			};
			virtual std::string ToJson() {
				std::ostringstream str;
				str << "{";
				str << "\"extension\" : \"" << this->Extension << "\"";
				str << ", \"name\" : \"" << this->VersionName << "\"";
				str << ", \"version\" : " << this->Version;
				str << ", \"brand\" : \"" << this->Brand << "\"";
				str << ", \"brandcode\" : \"" << this->BrandCode << "\"";
				str << "}";
				return str.str();
			}
			virtual std::string ToXml() {
				std::ostringstream str;
				str << "<item>";
				str << "<extension>" << this->Extension << "</extension>";
				str << "<name>" << this->VersionName << "</name>";
				str << "<version>" << this->Version << "</version>";
				str << "<brand>" << this->Brand << "</brand>";
				str << "<brandcode>" << this->BrandCode << "</brandcode>";
				str << "</item>";
				return str.str();
			}
			virtual std::string ToText() {
				std::ostringstream str;
				str << this->Extension;
				str << "\t" << this->VersionName;
				str << "\t" << this->Version;
				str << "\t" << this->BrandCode;
				str << "\t" << this->Brand;
				return str.str();
			}
			virtual std::string ToCsv() {
				std::ostringstream str;
				str << this->Extension;
				str << "," << this->VersionName;
				str << "," << this->Version;
				str << "," << this->BrandCode;
				str << "," << this->Brand;
				return str.str();
			}
		};

		//box types defined officially here: http://mp4ra.org/filetype.html    
		// and unofficially here: http://www.ftyps.com/
		std::string GetBrandName(std::string brandcode) {
			std::string ans;
			if (brandcode == "3g2a") { ans = "3GPP2"; }
			else if (brandcode == "3ge6") { ans = "3GPP Release 6 extended-presentation Profile"; }
			else if (brandcode == "3gg6") { ans = "3GPP Release 6 General Profile"; }
			else if (brandcode == "3gp4") { ans = "3GPP Release 4"; }
			else if (brandcode == "3gp5") { ans = "3GPP Release 5"; }
			else if (brandcode == "3gp6") { ans = "3GPP Release 6 basic Profile"; }
			else if (brandcode == "3gr6") { ans = "3GPP Release 6 progressive-download Profile"; }
			else if (brandcode == "3gs6") { ans = "3GPP Release 6 streaming-server Profile"; }
			else if (brandcode == "ARRI") { ans = "ARRI Digital Camera"; }
			else if (brandcode == "CAEP") { ans = "Canon Digital Camera"; }
			else if (brandcode == "CDes") { ans = "Convergent Designs"; }
			else if (brandcode == "LCAG") { ans = "Leica digital camera"; }
			else if (brandcode == "M4A ") { ans = "iTunes MPEG-4 audio"; }
			else if (brandcode == "M4B ") { ans = "iTunes AudioBook protected"; }
			else if (brandcode == "M4P ") { ans = "MPEG-4 protected audio"; }
			else if (brandcode == "M4V ") { ans = "MPEG-4 protected audio+video"; }
			else if (brandcode == "MPPI") { ans = "Photo Player Multimedia Application Format"; }
			else if (brandcode == "ROSS") { ans = "Ross Video"; }
			else if (brandcode == "avc1") { ans = "Advanced Video Coding extensions"; }
			else if (brandcode == "caqv") { ans = "Casio Digital Camera"; }
			else if (brandcode == "da0a") { ans = "DMB AF audio with MPEG Layer II audio, MOT slide show, DLS, JPG/PNG/MNG images"; }
			else if (brandcode == "da0b") { ans = "DMB AF, extending da0a , with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "da1a") { ans = "DMB AF audio with ER-BSAC audio, JPG/PNG/MNG images"; }
			else if (brandcode == "da1b") { ans = "DMB AF, extending da1a, with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "da2a") { ans = "DMB AF audio with HE-AAC v2 audio, MOT slide show, DLS, JPG/PNG/MNG images"; }
			else if (brandcode == "da2b") { ans = "DMB AF extending da2a, with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "da3a") { ans = "DMB AF audio with HE-AAC, JPG/PNG/MNG images"; }
			else if (brandcode == "da3b") { ans = "DMB AF extending da3a with BIFS, 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "dece") { ans = "Conforming to DECE 1.0 (UltraViolet)"; }
			else if (brandcode == "dmb1") { ans = "DMB AF supporting all the components defined in the specification"; }
			else if (brandcode == "dv1a") { ans = "DMB AF video with AVC video, ER-BSAC audio, BIFS, JPG/PNG/MNG images, TS"; }
			else if (brandcode == "dv1b") { ans = "DMB AF, extending dv1a, with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "dv2a") { ans = "DMB AF video with AVC video, HE-AACv2 audio, BIFS, JPG/PNG/MNG images, TS"; }
			else if (brandcode == "dv2b") { ans = "DMB AF extending dv2a, with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "dv3a") { ans = "DMB AF video with AVC video, HE-AAC audio, BIFS, JPG/PNG/MNG images, TS"; }
			else if (brandcode == "dv3b") { ans = "DMB AF extending dv3a with 3GPP timed text, DID, TVA, REL, IPMP"; }
			else if (brandcode == "dvr1") { ans = "DVB RTP"; }
			else if (brandcode == "dvt1") { ans = "DVB Transport Stream"; }
			else if (brandcode == "isc2") { ans = "Files encrypted according to ISMACryp 2.0"; }
			else if (brandcode == "iso2") { ans = "All files based on the 2004 edition of the ISO file format"; }
			else if (brandcode == "iso3") { ans = "Version of the ISO file format"; }
			else if (brandcode == "iso4") { ans = "Version of the ISO file format"; }
			else if (brandcode == "isom") { ans = "All files based on the ISO Base Media File Format"; }
			else if (brandcode == "jpsi") { ans = "The JPSearch data interchange format"; }
			else if (brandcode == "mj2s") { ans = "Motion JPEG 2000 simple profile"; }
			else if (brandcode == "mjp2") { ans = "Motion JPEG 2000, general profile"; }
			else if (brandcode == "mp21") { ans = "MPEG-21"; }
			else if (brandcode == "mp41") { ans = "MP4 version 1"; }
			else if (brandcode == "mp42") { ans = "MP4 version 2"; }
			else if (brandcode == "mp71") { ans = "MPEG-7 file-level metadata"; }
			else if (brandcode == "niko") { ans = "Nikon Digital Camera"; }
			else if (brandcode == "odcf") { ans = "OMA DCF (DRM Content Format)"; }
			else if (brandcode == "opf2") { ans = "OMA PDCF (DRM Content Format)"; }
			else if (brandcode == "opx2") { ans = "OMA Adapted PDCF"; }
			else if (brandcode == "pana") { ans = "Panasonic Digital Camera"; }
			else if (brandcode == "piff") { ans = "Protected Interoperable File Format"; }
			else if (brandcode == "qt  ") { ans = "QuickTime"; }
			else if (brandcode == "sdv ") { ans = "SD Video"; }
			else ans = "Unknonw FTYP";
			return ans;
		}

		std::vector<common::ExtensionInfo*> Detailer(std::string file, std::vector<unsigned char> buffer) {
			std::vector<common::ExtensionInfo*> ans;

			Mp4ExtensionInfo* ei = new Mp4ExtensionInfo();

			//Read major version
			ei->Version = common::ReadUInt(buffer.data(), buffer.size(), 12);

			std::vector<unsigned char> majorBlock(&buffer[8], &buffer[12]);
			std::string brandcode;
			brandcode.append(majorBlock.begin(), majorBlock.end());
			ei->BrandCode = brandcode;
			ei->Brand = GetBrandName(brandcode);

			ans.push_back(ei);
			return ans;
		}
	}
}