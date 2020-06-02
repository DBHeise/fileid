#pragma once
#include <string>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include "../common.hpp"
#include "pole.h"
#include "./propset/DocumentSummary.hpp"

namespace oless {

	//OpenFile - opens an OLESS file
	POLE::Storage* OpenFile(const char* file) {
		POLE::Storage* storage = new POLE::Storage(file);
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


	//GetStructFromStream - reads a given Struct from the first bytes of the stream
	template<typename T> T* GetStructFromStream(POLE::Stream* stream) {
		size_t size = sizeof(T);
		unsigned char* bytes = new unsigned char[size];

		POLE::uint64 read = stream->read(bytes, size);
		if (read > size) {
			throw std::runtime_error("how is this even possible!");
		}
		T* s = (T*)bytes;

		return s;
	}

	//ReadStream - reads an entire stream into a vector
	std::vector<uint8_t> ReadStream(POLE::Storage* storage, const std::wstring streamName) {
		std::vector<uint8_t> ans;

		auto stream = new POLE::Stream(storage, streamName);

		POLE::uint64 size = stream->size();
		unsigned char* buffer = new unsigned char[size];

		if (stream->read(buffer, size) == size) {
			ans.insert(ans.end(), &buffer[0], &buffer[size]);
		}
		delete stream;

		return ans;
	}

	typedef void (*OlessDataFunc)(common::ExtensionInfo*&, const std::string, const POLE::Storage*, const std::wstring, const std::vector<uint8_t>);

	struct OlessInfo {
		std::string Extension;
		std::string Name;
		std::string Version;
		std::string SubType;
		bool ignoreCase;
		OlessDataFunc extraFunc;
		std::wstring matcher;
		OlessInfo(const char* ext, const char* n, const char* ver, const char* sub, bool ignore, const wchar_t* match, OlessDataFunc ename) {
			std::string t(ext);
			this->Extension = t;
			std::string n2(n);
			this->Name = n2;
			std::string v(ver);
			this->Version = v;
			this->ignoreCase = ignore;
			std::wstring m(match);
			this->matcher = m;
			this->extraFunc = ename;
		}
	};


	class OLESSExtensionInfo : public common::ExtensionInfo {
	protected:
		virtual std::string buildBaseJson() const override {
			std::ostringstream str;
			str << common::ExtensionInfo::buildBaseJson();
			if (this->paths.size() > 0) {
				str << ", \"Paths\": [";
				for (auto i = this->paths.begin(); i != this->paths.end(); i++) {
					if (i != this->paths.begin()) str << ",";
					str << "\"" << common::JsonEscape(common::convert((i)->c_str())) << "\"";
				}
				str << "]";
			}
			if (this->properties.size() > 0) {
				str << ",\"properties\": [";
				for (auto n = this->properties.begin(); n != this->properties.end(); n++) {
					if (n != this->properties.begin()) str << ",";
					std::wstring key = n->first;
					std::vector<propset::Property*> props = n->second;

					str << "{\"Group\":\"" << common::JsonEscape(common::convert(key)) << "\",\"properties\": [";

					for (auto i = props.begin(); i != props.end(); i++) {
						if (i != props.begin()) str << ",";
						str << (*i)->ToJson();
					}
					str << "]}";
				}
				str << "]";
			}
			return str.str();
		}
		virtual std::string buildBaseXml() const override{
			std::ostringstream str;
			str << common::ExtensionInfo::buildBaseXml();
			if (this->paths.size() > 0) {
				str << "<Paths>";
				for (auto i = this->paths.begin(); i != this->paths.end(); i++) {
					if (i != this->paths.begin()) str << ",";
					str << "<Path>" << common::XmlEscape(common::convert((i)->c_str())) << "</Path>";
				}
				str << "</Paths>";
			}
			if (this->properties.size() > 0) {
				str << "<properties>";
				for (auto n = this->properties.begin(); n != this->properties.end(); n++) {
					std::wstring key = n->first;
					std::vector<propset::Property*> props = n->second;

					str << "<Group>";
					str << "<Name>" << common::XmlEscape(common::convert(key)) << "</Name>";
					str << "<properties>";
					for (auto i = props.begin(); i != props.end(); i++) {
						str << (*i)->ToXML();
					}
					str << "</properties>";
					str << "</Group>";
				}
				str << "</properties>";
			}
			return str.str();
		}
	public:
		std::vector<std::wstring> paths;
		std::map<std::wstring, std::vector<propset::Property*>> properties;		
		OLESSExtensionInfo() {
			this->Extension = "oless";
			this->VersionName = "OLE Structured Storage";
		}

		virtual std::string ToJson() const override {
			std::ostringstream str;
			str << "{";
			str << this->buildBaseJson();			
			str << "}";
			return str.str();
		}
		virtual std::string ToXml() const override {
			std::ostringstream str;
			str << "<item>";
			str << this->buildBaseXml();
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() const override {
			std::ostringstream str;
			str << this->Extension;
			str << "\t" << this->VersionName;
			str << "\t" << this->Version;
			return str.str();
		}
		virtual std::string ToCsv() const override {
			std::ostringstream str;
			str << this->Extension;
			str << "," << this->VersionName;
			str << "," << this->Version;
			return str.str();
		}
	};

	class OleSummary : public common::IExportable {
	public:
		std::string FullName;
		unsigned long long Size;

		virtual std::string ToJson() const {
			std::ostringstream str;
			str << "{ \"path\" : \"" << common::JsonEscape(this->FullName) << "\", \"size\" : \"" << this->Size << "\"}";
			return str.str();
		}
		virtual std::string ToXml() const {
			std::ostringstream str;
			str << "<item>";
			str << "<path>" << common::XmlEscape(this->FullName) << "</path>";
			str << "<size>" << this->Size << "</size>";
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() const {
			std::ostringstream str;
			str << this->FullName << "\t" << this->Size;
			return str.str();
		}
		virtual std::string ToCsv() const {
			std::ostringstream str;
			str << this->FullName << "," << this->Size;
			return str.str();
		}
	};
}