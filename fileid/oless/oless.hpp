#pragma once

#include <list>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"
#include "olessoffice.hpp"
#include "vbahelper.hpp"
#include "WordPerfect.hpp"
#include "./propset/DocumentSummary.hpp"


namespace oless {

	POLE::Storage* OpenFile(const char* file) {
		POLE::Storage *storage = new POLE::Storage(file);
		storage->open();
		if (storage->result() != POLE::Storage::Ok)
		{
			storage->close();			
			delete storage;
			return NULL;
		}
		else {
			return storage;
		}		
	}

	template<class T>
	std::vector<T*> convert(std::vector<common::IExportable*> vector) {
		std::vector<T*> ans;
		std::vector<common::IExportable*>::iterator it;
		for (it = vector.begin(); it != vector.end(); ++it) {
			ans.push_back((T*)(*it));
		}
		return ans;
	}

	class Oless {
	private:
		const char* m_file;
		std::vector<std::string> m_paths;
		std::vector<common::IExportable*> m_results;
		std::map<std::string, std::vector<propset::Property*>> m_properties;

		void printStreamInfo(POLE::Storage* storage, std::wstring name, std::wstring fullname)
		{
			if (!storage->isDirectory(fullname)) {
				POLE::Stream *stream = new POLE::Stream(storage, fullname.c_str());
				if (!stream->fail()) {
					OleSummary *summary = new OleSummary();
					summary->FullName = common::convert(stream->fullName());
					summary->Size = stream->size();
					this->m_results.push_back((common::IExportable*)summary);
				}
			}
		}
		void guessStreamInfo(POLE::Storage* storage, std::wstring name, std::wstring fullname) {
			olessoffice *oo = new olessoffice();
			common::ExtensionInfo* ei = nullptr;

			if (storage->isDirectory(fullname)) {
				//Storage Analysis
				if (name == L"Macros" || name == L"_VBA_PROJECT_CUR" || fullname == L"/VBA" || fullname == L"/VBA_Project") {
					VBA::vbahelper* vba = new VBA::vbahelper();
					delete ei;
					try {
						ei = vba->Analyze(fullname, storage);
					}
					catch (std::exception ex) {
						ei = new VBA::VbaExtensionInfo();
						((VBA::VbaExtensionInfo*)ei)->ProjectName = ex.what();
						((VBA::VbaExtensionInfo*)ei)->SubType = "ERROR";
					}
				}
			}
			else {
				//Stream Analysis
				if (fullname == L"/DRMContent") {
					ei = new OLESSExtensionInfo();
					ei->Extension = "irm";
					ei->Name = "Microsoft Office Information Rights Managed File";
					ei->SubType = "drm";
				}
				else if (fullname == L"/PowerPoint Document") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "ppt";
					ei->Name = "Microsoft Office PowerPoint Document";
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					ei->Version = oo->GetPptVersion(storage, stream);
					ei->VersionName = oo->GetVersion_Powerpoint(ei->Version);
					ei->SubType = ei->VersionName;
				}
				else if (fullname == L"/PP40") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "ppt";
					ei->Name = "Microsoft Office PowerPoint Document";
					ei->Version = 4;
					ei->VersionName = "PowerPoint 4.0";
					ei->SubType = ei->VersionName;
				}
				else if (common::iequals(fullname, L"/Workbook") || common::iequals(fullname, L"/Book")) {
					ei = new excel::ExcelExtensionInfo();
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					((excel::ExcelExtensionInfo*)ei)->ParseStream(stream);
					delete stream;
				}
				else if (fullname == L"/WordDocument") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "doc";
					ei->Name = "Microsoft Office Word Document";
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					ei->Version = oo->GetnFib(stream);
					ei->VersionName = oo->GetVersion_Word(ei->Version);
					ei->SubType = ei->VersionName;
					delete stream;
				}
				else if (fullname == L"/Contents") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "pub";
					ei->Name = "Microsoft Office Publisher Document";
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					ei->Version = oo->GetPubVersion(stream);
					ei->VersionName = oo->GetVersion_Publisher(ei->Version);
					ei->SubType = ei->VersionName;
					delete stream;
				}
				else if (fullname == L"/VisioDocument") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "vsd";
					ei->Name = "Microsoft Office Visio Document";
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					ei->Version = oo->GetVisoVersion(stream);
					ei->VersionName = oo->GetVersion_Visio(ei->Version);
					ei->SubType = ei->VersionName;
					delete stream;
				}
				else if (fullname == L"/Details") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "bup";
					//extract bup data!
				}
				else if (fullname == L"/__properties_version1.0") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "msg";
					ei->Name = "Mail Message";
				}
				else if (fullname == L"/DataSpaces/DataSpaceMap") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "irm";
					ei->Name = "Encrypted Office Document";
					ei->SubType = "encrypted";
				}
				else if (fullname == L"/Props9") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "mpp";
					ei->Version = 9;
					ei->VersionName = "Project 9";
					ei->SubType = "Office 2003";
					ei->Name = "Microsoft Project File";
				}
				else if (fullname == L"/Props12") {
					ei = new OLESSExtensionInfo();
					ei->Extension = "mpp";
					ei->Version = 12;
					ei->VersionName = "Project 12";
					ei->SubType = "Office 2007";
					ei->Name = "Microsoft Project File";
				}
				else if (fullname == L"/Props14") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "mpp";
					ei->Version = 14;
					ei->VersionName = "Project 14";
					ei->SubType = "Office 2010";
					ei->Name = "Microsoft Project File";
				}
				else if (fullname == L"/Binder") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "obd";
					ei->Name = "Microsoft Office Binder";
				}
				else if (fullname == L"/CONTENTS" || fullname == L"/MatOST") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "wps";
					ei->Name = "Microsoft Works File";
				}
				else if (fullname == L"/StarCalcDocument") {
					ei = new OLESSExtensionInfo();
					ei->Extension = "sdc";
					ei->Name = "StarOffice Calc";
				}
				else if (fullname == L"/StarWriterDocument") {
					ei = new OLESSExtensionInfo(); 
					ei->Extension = "sdw";
					ei->Name = "StarOffice Write";
				}
				//else if (fullname == L"/StarDrawDocument3") {
					//ei->Extension = "sda"; //sxd
					//ei->Name = "StarOffice Draw";
					//ei->Extension = "sdd"; //sxi
					//ei->Name = "StarOffice Draw";
				//}
				else if (fullname == L"/HwpSummaryInformation") {
					ei = new OLESSExtensionInfo();
					ei->Extension = "hwp";
					ei->Name = "Hangul Word Processor File";
				}
				else if (fullname == L"/PerfectOffice_MAIN") {
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					ei = WordPerfect::ReadWPStream(stream);
					delete stream;
				}
				else if (name == L"\u0005DocumentSummaryInformation"  || name== L"\x5SummaryInformation" || name == L"GlobalInfo" || name == L"ImageContents" || name == L"ImageInfo") {
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					try {
						auto props = propset::ParseStream(stream);
						this->m_properties.insert(std::pair<std::string, std::vector<propset::Property*>>(common::convert(fullname), props));
					}
					catch (const std::range_error) {
#ifdef DEBUG
						std::cerr << "Error Parsing PropertyStream: [" << common::convert(fullname) << "]" << std::endl;
#endif
					}
					delete stream;
				}
				else if (name == L"䡀㬿䏲䐸䖱") { //MSI String Table
					ei = new OLESSExtensionInfo();
					ei->Extension = "msi";
					ei->Name = "Microsoft Installer File";
				}
			}
			if (ei != nullptr) {
				this->m_results.push_back((common::IExportable*)ei);
			}
			delete oo;
		}
		void recurse(POLE::Storage* storage, const std::wstring path, void(Oless::*pCallback)(POLE::Storage*, std::wstring, std::wstring)) {
			this->m_paths.push_back(common::convert(path));
			std::list<std::wstring> entries;
			entries = storage->entries(path);

			for (auto it = entries.begin(); it != entries.end(); it++)
			{
				std::wstring name = *it;
				std::wstring fullname = path + name;
				
				(this->*pCallback)(storage, name, fullname);
				if (storage->isDirectory(fullname))
				{
					this->recurse(storage, fullname + L"/", pCallback);
				}
				else 
				{
					this->m_paths.push_back(common::convert(fullname));
				}
			}
		}

	public:
		Oless() {};
		Oless(const char* file) {
			m_file = file;
		}
		std::vector<common::ExtensionInfo*> Guess() {
			this->m_results.clear();
			POLE::Storage *storage = OpenFile(this->m_file);
			if (storage) {
				this->recurse(storage, L"/", &Oless::guessStreamInfo);
				storage->close();
				delete storage;
			}
			if (this->m_results.size() == 0) {
				auto ei = new OLESSExtensionInfo();
				ei->paths = this->m_paths;
				ei->properties = this->m_properties;
				this->m_results.push_back((common::IExportable*)ei);
			} else {
				for (auto i = this->m_results.begin(); i != this->m_results.end(); i++) {
					if (OLESSExtensionInfo* e = dynamic_cast<OLESSExtensionInfo*>(*i)) {
						e->paths = this->m_paths;
						e->properties = this->m_properties;
						break;
					}
				}
			}

			return convert<common::ExtensionInfo>(this->m_results);
		}
		std::vector<OleSummary*> List() {
			this->m_results.clear();
			POLE::Storage *storage = new POLE::Storage(this->m_file);
			storage->open();

			if (storage->result() != POLE::Storage::Ok)
			{
				std::cerr << "Unable to open OLESS file" << std::endl;
			}
			else {
				this->recurse(storage, L"/", &Oless::printStreamInfo);
			}

			storage->close();
			delete storage;

			return convert<OleSummary>(this->m_results);
		}

		void Dump(std::wstring name, std::string outFile) {
			POLE::Storage *storage = OpenFile(this->m_file);
			if (storage) {
				POLE::Stream *stream = new POLE::Stream(storage, name);
				if (stream && !stream->fail()) {
					std::ofstream file;
					file.open(outFile, std::ios::out | std::ios::binary);
					unsigned char buffer[16];
					for (;;) {
						POLE::uint64 read = stream->read(buffer, sizeof(buffer));
						file.write((const char*)buffer, read);
						if (read < sizeof(buffer)) break;
					}
					file.close();
				}
				else {
					std::cerr << "Unable to open stream" << std::endl;
				}
				storage->close();
				delete storage;
			}
		}
		bool IsOless() {
			bool ans = true;
			std::ifstream file;
			file.open(this->m_file, std::ios::in | std::ios::binary);
			unsigned char mustbe[] = { 0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1 };
			char *buffer = new char[8];
			file.read(buffer, 8);
			for (int i = 0; i < 8; i++) {
				ans &= (((unsigned char)buffer[i]) == mustbe[i]);
			}
			return ans;
		};

	};

	std::vector<common::ExtensionInfo*> Detailer(std::string file, std::vector<unsigned char> buffer) {
		Oless* o = new Oless(file.c_str());
		return o->Guess();
	}
}