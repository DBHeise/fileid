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
#include "../common.hpp"
#include "../oless/vbahelper.hpp"
#include "../../ziplib/Source/ZipLib/ZipFile.h"
#include "../../ziplib/Source/ZipLib/ZipArchive.h"
#include "../../ziplib/Source/ZipLib/ZipArchiveEntry.h"

namespace zip {
	inline void CheckEntry(ZipArchive::Ptr archive, std::vector<common::ExtensionInfo*>* vlist, std::string file, std::string extension, std::string name) {
		ZipArchiveEntry::Ptr entry = archive->GetEntry(file);
		if (entry) {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = extension;
			ext->Name = name;
			vlist->push_back(ext);
		}
	}

	void CheckContentType(std::vector<common::ExtensionInfo*>* vlist, std::string contentType)
	{
		if (contentType == "application/vnd.ms-word.document.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "docm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Document";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-word.template.macroEnabledTemplate.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "dotm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Document Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "docx";
			ext->Name = "Microsoft Office Open XML Document";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.wordprocessingml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "dotx";
			ext->Name = "Microsoft Office Open XML Document Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.template.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "potm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.slideshow.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppsm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation Slideshow";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.presentation.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "pptm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Presentation";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "potx";
			ext->Name = "Microsoft Office Open XML Presentation Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-powerpoint.addin.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppam";
			ext->Name = "Microsoft Office Open XML Presentation Macro-Enabled Addin";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.slideshow.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ppsx";
			ext->Name = "Microsoft Office Open XML Presentation Slideshow";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.presentationml.presentation.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "pptx";
			ext->Name = "Microsoft Office Open XML Presentation";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-excel.sheet.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Spreadsheet";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-excel.template.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xltm";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Spreadsheet Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsx";
			ext->Name = "Microsoft Office Open XML Spreadsheet";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-excel.addin.macroEnabled.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlam";
			ext->Name = "Microsoft Office Open XML Macro-Enabled Addin";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.openxmlformats-officedocument.spreadsheetml.template.main+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xltx";
			ext->Name = "Microsoft Office Open XML Spreadsheet Template";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-excel.worksheet" || contentType == "application/vnd.ms-excel.main") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xlsb";
			ext->Name = "Microsoft Office Excel Binary";
			vlist->push_back(ext);
		}
		else if (contentType == "application/vnd.ms-package.xps-fixeddocumentsequence+xml") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "xps";
			ext->Name = "Microsoft XML Paper Specfication";
			vlist->push_back(ext);
		}
	}

	void CheckMimeType(std::vector<common::ExtensionInfo*>* vlist, std::string mimeType) {
		if (mimeType == "application/vnd.oasis.opendocument.text") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odt";
			ext->Name = "Open Document Text";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.spreadsheet") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ods";
			ext->Name = "Open Document Spreadsheet";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.presentation") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "opd";
			ext->Name = "Open Document Presentation";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.graphics") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odg";
			ext->Name = "Open Document Graphics";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.chart") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odc";
			ext->Name = "Open Document Chart";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.formula") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odf";
			ext->Name = "Open Document Formula";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.image") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odi";
			ext->Name = "Open Document Image";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-master") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odm";
			ext->Name = "Open Document Text-Master";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.sun.xml.base" || mimeType == "application/vnd.oasis.opendocument.base" || mimeType == "application/vnd.oasis.opendocument.database") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "odb";
			ext->Name = "Open Document Database";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ott";
			ext->Name = "Open Document Text Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.spreadsheet-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "ots";
			ext->Name = "Open Document Spreadsheet Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.presentation-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otp";
			ext->Name = "Open Document Presentation Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.graphics-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otg";
			ext->Name = "Open Document Graphics Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.chart-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otc";
			ext->Name = "Open Document Chart Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.formula-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "otf";
			ext->Name = "Open Document Formula Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.image-template") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "oti";
			ext->Name = "Open Document Image Template";
			vlist->push_back(ext);
		}
		else if (mimeType == "application/vnd.oasis.opendocument.text-web") {
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "oth";
			ext->Name = "Open Document Webpage";
			vlist->push_back(ext);
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

	common::ExtensionInfo* GetVBA(ZipArchive::Ptr archive) {
		OleStructuredStorage::VBA::vbahelper* vba = new OleStructuredStorage::VBA::vbahelper();
		common::ExtensionInfo *ei = new common::ExtensionInfo();
		//temp fix
		ei->Extension = "vba";
		ei->Name = "Visual Basic For Applications";

		//TODO: find vba binary in zip file, and decompress it in memory

		//TODO: Modify POLE to take a stream
		/*POLE::Storage *storage = new POLE::Storage();
		try {
			ei = vba->Analyze("/", storage);
		}
		catch (std::exception ex) {
			ei = new OleStructuredStorage::VBA::VbaExtensionInfo();
			((OleStructuredStorage::VBA::VbaExtensionInfo*)ei)->ProjectName = ex.what();
			((OleStructuredStorage::VBA::VbaExtensionInfo*)ei)->SubType = "ERROR";
		}*/
		return ei;
	}

	std::vector<common::ExtensionInfo*> Detailer(const std::string file, std::vector<unsigned char> buffer) {
		std::vector<common::ExtensionInfo*> ans;
		ZipArchive::Ptr archive = ZipFile::Open(file);
		//archive->GetEntriesCount();
		//archive->GetComment();

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
							ans.push_back(GetVBA(archive));
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
			common::ExtensionInfo* ext = new common::ExtensionInfo();
			ext->Extension = "zip";
			ext->Name = "ZIP File";
			ans.push_back(ext);
		}
		return ans;
	}
}
