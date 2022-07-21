#pragma once
#if (defined(__GNUC__) && (__GNUC__ == 4)) // We do not care of GCC prior 4.x (without any form of C++11 support)
/// GCC 4.7 and following have "override" and "final" support when called with -std=c++0x (or -std=c++11 starting with GCC 4.7)
#if ((__GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
/// GCC 4.6 and below does not know the "override" specifier, so we define it as nothing
#error Must have GCC 4.7 or greater
#endif
#endif

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <streambuf>
#include <cstdio>
#include "../common.hpp"
#include "../oless/vbahelper.hpp"
#include "../../ziplib/Source/ZipLib/ZipFile.h"
#include "../../ziplib/Source/ZipLib/ZipArchive.h"
#include "../../ziplib/Source/ZipLib/ZipArchiveEntry.h"
#include "../../ziplib/Source/ZipLib/utils/stream_utils.h"

namespace zip {

	struct ZipFileInfo {
	public:
		std::string Name;
		std::size_t Size;
		int CompressedSize;
		bool IsPassworded;
		std::string CompressionMethod;
		std::string Comment;
		unsigned int CRC32;

	};

	class ZipExtensionInfo : public common::ExtensionInfo {
	public:
		std::vector<ZipFileInfo*> children;
		ZipExtensionInfo() : ExtensionInfo() {
			this->Extension = "zip";
			this->Name = "Zip File";
			this->Version = 0;
			this->VersionName = "";
		};

		virtual std::string ToJson() {
			std::ostringstream str;
			str << "{ \"extension\" : \"" << this->Extension << "\"";
			if (this->Name.size() > 0) {
				str << ", \"name\":\"" << this->Name << "\"";
			}
			if (this->SubType.size() > 0) {
				str << ", \"subtype\":\"" << common::JsonEscape(this->SubType) << "\"";
			}
			if (this->children.size() > 0) {
				str << ", \"children\":[";
				for (std::vector<ZipFileInfo*>::const_iterator i = this->children.begin(); i != this->children.end(); i++) {
					if (i != this->children.begin()) str << ",";
					str << "{";
					str << "\"Name\":\"" << (*i)->Name << "\"";
					str << ", \"Size\":\"" << std::to_string((*i)->Size) << "\"";
					str << ", \"CompressedSize\":\"" << std::to_string((*i)->CompressedSize) << "\"";
					str << ", \"CompressionMethod\":\"" << (*i)->CompressionMethod << "\"";
					str << ", \"IsPassworded\":\"" << (*i)->IsPassworded << "\"";
					str << ", \"Comment\":\"" << (*i)->Comment << "\"";
					str << ", \"CRC32\":\"" << std::to_string((*i)->CRC32) << "\"";
					str << "}";
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
			if (this->Name.size() > 0) {
				str << "<name>" << this->Name << "</name>";
			}
			if (this->SubType.size() > 0) {
				str << "<subtype>" << common::XmlEscape(this->SubType) << "</subtype>";
			}
			if (this->children.size() > 0) {
				str << "<children>";
				for (std::vector<ZipFileInfo*>::const_iterator i = this->children.begin(); i != this->children.end(); i++) {
					str << "<file>";
					str << "<Name>" << (*i)->Name << "</Name>";
					str << "<Size>" << std::to_string((*i)->Size) << "</Size>";
					str << "<CompressedSize>" << std::to_string((*i)->CompressedSize) << "</CompressedSize>";
					str << "<CompressionMethod>" << (*i)->CompressionMethod << "</CompressionMethod>";
					str << "<IsPassworded>" << (*i)->IsPassworded << "</IsPassworded>";
					str << "<Comment>" << (*i)->Comment << "</Comment>";
					str << "<CRC32>" << std::to_string((*i)->CRC32) << "</CRC32>";
					str << "</file>";
				}
				str << "</children>";
			}
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() {
			std::ostringstream str;
			str << this->Extension;
			str << "\t" << this->Name;
			str << "\t" << this->SubType;
			str << "\t" << this->Version;
			str << "\t" << this->VersionName;
			return str.str();
		}
		virtual std::string ToCsv() {
			std::ostringstream str;
			str << this->Extension;
			str << "," << this->Name;
			str << "," << this->SubType;
			str << "," << this->Version;
			str << "," << this->VersionName;
			return str.str();
		}

	};
	
	bool hasEnding(std::string const &fullString, std::string const &ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	inline void CheckEntry(ZipArchive::Ptr archive, std::vector<common::ExtensionInfo*>* vlist, std::string file, std::string extension, std::string name) {
		ZipArchiveEntry::Ptr entry = archive->GetEntry(file);
		if (entry) {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = extension;
			ext->Name = name;
			vlist->push_back(ext);
		}
	}
	std::map<std::string, bool> extMap;
	inline void addExtension(std::vector<common::ExtensionInfo*>* vlist, common::ExtensionInfo* item) {
		auto it = extMap.find(item->Extension);
		if (it == extMap.end()) {
			vlist->push_back(item);
			extMap[item->Extension] = true;
		}
	}


	void CheckContentType(std::vector<common::ExtensionInfo*>* vlist, std::string contentType)
	{
		     if (contentType == "application/vnd.ms-word.document.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "docm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Document";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-word.template.macroEnabledTemplate.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "dotm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Document Template";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "docx";
			ext->Name = "Microsoft Office Open XML Document";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.wordprocessingml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "dotx";
			ext->Name = "Microsoft Office Open XML Document Template";
			addExtension(vlist, ext);
		}

		else if (contentType == "application/vnd.ms-powerpoint.template.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "potm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation Template";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.slideshow.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppsm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation Slideshow";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "pptm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.addin.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppam";
			ext->Name = "Microsoft Office Open XML Presentation Macro-Enabled Addin";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "potx";
			ext->Name = "Microsoft Office Open XML Presentation Template";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.slideshow.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppsx";
			ext->Name = "Microsoft Office Open XML Presentation Slideshow";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.presentation.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "pptx";
			ext->Name = "Microsoft Office Open XML Presentation";
			addExtension(vlist, ext);
		}

		else if (contentType == "application/vnd.ms-excel.sheet.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Spreadsheet";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-excel.worksheet" || contentType == "application/vnd.ms-excel.main") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsb";
			ext->Name = "Microsoft Office Excel Binary";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-excel.macrosheet") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsb_e4m";
			ext->Name = "Microsoft Office Excel Binary with Excel4.0Macros";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-excel.macrosheet+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsm_e4m";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Spreadsheet with Excel4.0Macros";
			addExtension(vlist, ext);
		}

		else if (contentType == "application/vnd.ms-excel.template.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xltm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Spreadsheet Template";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.ms-excel.addin.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlam";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Addin";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsx";
			ext->Name = "Microsoft Office Open XML Spreadsheet";
			addExtension(vlist, ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.spreadsheetml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xltx";
			ext->Name = "Microsoft Office Open XML Spreadsheet Template";
			addExtension(vlist, ext);
		}

		else if (contentType == "application/vnd.ms-package.xps-fixeddocumentsequence+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xps";
			ext->Name = "Microsoft XML Paper Specfication";
			addExtension(vlist, ext);
		}
	}

	void CheckMimeType(std::vector<common::ExtensionInfo*>* vlist, std::string mimeType) {
		if (mimeType == "application/vnd.oasis.opendocument.text") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odt";
			ext->Name = "Open Document Text";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.spreadsheet") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ods";
			ext->Name = "Open Document Spreadsheet";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.presentation") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "opd";
			ext->Name = "Open Document Presentation";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.graphics") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odg";
			ext->Name = "Open Document Graphics";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.chart") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odc";
			ext->Name = "Open Document Chart";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.formula") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odf";
			ext->Name = "Open Document Formula";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.image") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odi";
			ext->Name = "Open Document Image";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-master") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odm";
			ext->Name = "Open Document Text-Master";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.sun.xml.base" || mimeType == "application/vnd.oasis.opendocument.base" || mimeType == "application/vnd.oasis.opendocument.database") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odb";
			ext->Name = "Open Document Database";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ott";
			ext->Name = "Open Document Text Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.spreadsheet-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ots";
			ext->Name = "Open Document Spreadsheet Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.presentation-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otp";
			ext->Name = "Open Document Presentation Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.graphics-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otg";
			ext->Name = "Open Document Graphics Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.chart-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otc";
			ext->Name = "Open Document Chart Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.formula-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otf";
			ext->Name = "Open Document Formula Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.image-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "oti";
			ext->Name = "Open Document Image Template";
			addExtension(vlist, ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-web") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "oth";
			ext->Name = "Open Document Webpage";
			addExtension(vlist, ext);
		}
	}

	std::string GetFile(ZipArchiveEntry::Ptr entry) {
		std::string ans;
		std::istream* decompStream = nullptr;
		decompStream = entry->GetDecompressionStream();
		if (decompStream != nullptr) {
			std::stringstream buffer;
			buffer << decompStream->rdbuf();
			ans = buffer.str();
		}
		return ans;
	}

	common::ExtensionInfo* GetVBA(ZipArchive::Ptr archive, ZipExtensionInfo* details) {
		auto vba = new oless::VBA::vbahelper();
		auto *ei = new common::ExtensionInfo();
		//temp fix
		ei->Extension = "vba";
		ei->Name = "Visual Basic For Applications";

		//find vba binary in zip file
		std::vector<std::string> binFiles;
		for (std::vector<ZipFileInfo*>::const_iterator i = details->children.begin(); i != details->children.end(); i++) {
			std::string file = (*i)->Name;
			if (hasEnding(file, "bin")) { //TODO: read this extension from the XML
				binFiles.push_back(file);
			}
		}

		for (std::vector<std::string>::const_iterator i = binFiles.begin(); i != binFiles.end(); i++) {
			ZipArchiveEntry::Ptr entry = archive->GetEntry((*i));

			//TODO: Modify POLE to take a stream

			std::istream* stream = entry->GetDecompressionStream();
			std::ofstream outFile;
			auto tmpFile = common::get_temp_file();
			outFile.open(tmpFile);			
			
			utils::stream::copy(*stream, outFile);

			outFile.flush();
			outFile.close();

			POLE::Storage *storage = new POLE::Storage(tmpFile.c_str());
			try {
				ei = vba->Analyze(L"/", storage);
			}
			catch (std::exception ex) {
				ei = new oless::VBA::VbaExtensionInfo();
				((oless::VBA::VbaExtensionInfo*)ei)->ProjectName = ex.what();
				((oless::VBA::VbaExtensionInfo*)ei)->SubType = "ERROR";
			}

			remove(tmpFile.c_str());
		}
		return ei;
	}

	ZipExtensionInfo* getZipDetails(ZipArchive::Ptr archive) {
		ZipExtensionInfo* ans = new ZipExtensionInfo();
		size_t entries = archive->GetEntriesCount();

		for (size_t i = 0; i < entries; ++i) {
			std::shared_ptr<ZipArchiveEntry> entry = archive->GetEntry(int(i));
			ZipFileInfo* info = new ZipFileInfo();
			info->Name = entry->GetFullName();
			info->Size = entry->GetSize();
			info->CompressedSize = entry->GetCompressedSize();
			info->IsPassworded = entry->IsPasswordProtected();
			info->CompressionMethod = entry->GetCompressionMethod() == DeflateMethod::CompressionMethod ? "DEFLATE" : "stored";
			info->Comment = entry->GetComment();
			info->CRC32 = entry->GetCrc32();
			ans->children.push_back(info);
		}
		return ans;
	}

	std::vector<common::ExtensionInfo*> Detailer(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		ZipArchive::Ptr archive = ZipFile::Open(file);
		ZipExtensionInfo* details = getZipDetails(archive);

		CheckEntry(archive, &ans, "META-INF/MANIFEST.MF", "jar", "Java Archive");
		CheckEntry(archive, &ans, "WEB-INF/web.xml", "war", "Web Application Java Archive");
		CheckEntry(archive, &ans, "META-INF/application.xml", "ear", "Enterprise Java Archive");
		CheckEntry(archive, &ans, "AndroidManifest.xml", "apk", "Android Application Package");
		CheckEntry(archive, &ans, "install.js", "xpi", "Cross Platform Installer");
		CheckEntry(archive, &ans, "install.rdf", "xpi", "Cross Platform Installer");
		CheckEntry(archive, &ans, "AppManifest.xaml", "xap", "Silverlight Packaged Application");
		CheckEntry(archive, &ans, "WMAppManifest.xml", "xap", "Silverlight Phone Application");
		CheckEntry(archive, &ans, "Payload/Application.app", "ipa", "iOS Application Archive");
		CheckEntry(archive, &ans, "imsmanifest.xml", "scorm_pif", "SCORM (Shareable Content Object Reference Model) Content Package");



		/* TODO:
		KWD     KWord document
		SXC     StarOffice spreadsheet
		WMZ     Windows Media compressed skin file
		XPT     eXact Packager Models
		*/

		ZipArchiveEntry::Ptr ooxmlEntry = archive->GetEntry("[Content_Types].xml");
		if (ooxmlEntry) {
			std::string contentType = GetFile(ooxmlEntry);
			if (!contentType.empty()) {
				size_t start = contentType.find("ContentType=\"");
				while (start != std::string::npos) {
					start += 14;
					size_t end = contentType.find("\"", start);
					if (end != std::string::npos) {
						std::string ctype = contentType.substr(start - 1, end - start + 1);
						CheckContentType(&ans, ctype);

						if (ctype == "application/vnd.ms-office.vbaProject") {
							addExtension(&ans, GetVBA(archive, details));
						}
						start = contentType.find("ContentType=\"", end + 1);
					}
					else {
						start = end;
					}
				}
			}
			//ooxmlEntry->~ZipArchiveEntry();
		}

		ZipArchiveEntry::Ptr odEntry = archive->GetEntry("mimetype");
		if (odEntry) {
			std::string mimeType = GetFile(odEntry);
			if (!mimeType.empty()) {
				CheckMimeType(&ans, mimeType);
			}
			//odEntry->~ZipArchiveEntry();
		}

		if (ans.size() == 0) {
			ans.push_back(details);
		}
		return ans;
	}

}
