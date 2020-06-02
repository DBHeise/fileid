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
#include "vbahelper.hpp"
#include "./propset/DocumentSummary.hpp"
#include "olessmagic.h"

namespace oless {


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
		std::string m_file;
		std::vector<std::wstring> m_paths;
		std::vector<common::IExportable*> m_results;
		std::map<std::wstring, std::vector<propset::Property*>> m_properties;

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
				if (name == L"\u0005DocumentSummaryInformation" || name == L"\x5SummaryInformation" || name == L"GlobalInfo" || name == L"ImageContents" || name == L"ImageInfo") {
					POLE::Stream* stream = new POLE::Stream(storage, fullname);
					try {
						auto props = propset::ParseStream(stream);
						this->m_properties.insert(std::pair<std::wstring, std::vector<propset::Property*>>(fullname, props));
					}
					catch (const std::range_error) {
#ifdef DEBUG
						std::cerr << "Error Parsing PropertyStream: [" << common::convert(fullname) << "]" << std::endl;
#endif
					}
					delete stream;
				}
				else {					
					for (auto it = oless::magic::list.begin(); it != oless::magic::list.end(); it++) {
						auto olessMagic = (*it);

						//Match on fullname AND name
						//bool isMatch = (olessMagic->ignoreCase && (common::iequals(fullname, olessMagic->matcher) || common::iequals(name, olessMagic->matcher))) || (fullname == olessMagic->matcher || name == olessMagic->matcher);

						//Match on fullname ONLY
						bool isMatch = (olessMagic->ignoreCase && common::iequals(fullname, olessMagic->matcher)) || fullname == olessMagic->matcher;

						if (isMatch) {
							ei = new OLESSExtensionInfo();
							ei->Extension = olessMagic->Extension;
							ei->VersionName = olessMagic->Version;
							ei->SubType = olessMagic->SubType;
							ei->Name = olessMagic->Name;

							if (olessMagic->extraFunc != nullptr) {
								olessMagic->extraFunc(ei, this->m_file, storage, name, ReadStream(storage, fullname));
							}
						}
					}
				}
			}
			if (ei != nullptr) {
				this->m_results.push_back((common::IExportable*)ei);
			}
		}
		void recurse(POLE::Storage* storage, const std::wstring path, void(Oless::*pCallback)(POLE::Storage*, std::wstring, std::wstring)) {
			this->m_paths.push_back(path);
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
					this->m_paths.push_back(fullname);
				}
			}
		}

	public:
		Oless() {};
		Oless(const char* file) {
			std::string temp(file);
			this->m_file = temp;
		}
		std::vector<common::ExtensionInfo*> Guess() {
			this->m_results.clear();
			POLE::Storage *storage = OpenFile(this->m_file.c_str());
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
			POLE::Storage *storage = new POLE::Storage(this->m_file.c_str());
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
			POLE::Storage *storage = OpenFile(this->m_file.c_str());
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
		oless::magic::initList();
		Oless* o = new Oless(file.c_str());
		return o->Guess();
	}
}