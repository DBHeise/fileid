#pragma once
#include <string>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include "../common.hpp"
#include "./propset/DocumentSummary.hpp"

namespace oless {

	class OLESSExtensionInfo : public common::ExtensionInfo {
	protected:
		virtual std::string buildBaseJson() const override {
			std::ostringstream str;
			str << common::ExtensionInfo::buildBaseJson();
			if (this->paths.size() > 0) {
				str << ", \"Paths\": [";
				for (auto i = this->paths.begin(); i != this->paths.end(); i++) {
					if (i != this->paths.begin()) str << ",";
					str << "\"" << (i)->c_str() << "\"";
				}
				str << "]";
			}
			if (this->properties.size() > 0) {
				str << ",\"properties\": [";
				for (auto n = this->properties.begin(); n != this->properties.end(); n++) {
					if (n != this->properties.begin()) str << ",";
					std::string key = n->first;
					std::vector<propset::Property*> props = n->second;

					str << "{\"Group\":\"" << key << "\",\"properties\": [";

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
					str << "<Path>" << (i)->c_str() << "</Path>";
				}
				str << "</Paths>";
			}
			if (this->properties.size() > 0) {
				str << "<properties>";
				for (auto n = this->properties.begin(); n != this->properties.end(); n++) {
					std::string key = n->first;
					std::vector<propset::Property*> props = n->second;

					str << "<Group>";
					str << "<Name>" << key << "</Name>";
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
		std::vector<std::string> paths;
		std::map<std::string, std::vector<propset::Property*>> properties;		
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
			str << "<path>" << this->FullName << "</path>";
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

	class OleHelper {
	public:
		template<typename T>
		static  T* GetStructFromStream(POLE::Stream* stream) {
			size_t size = sizeof(T);
			unsigned char* bytes = new unsigned char[size];

			POLE::uint64 read = stream->read(bytes, size);
			if (read > size) {
				throw std::runtime_error("how is this even possible!");
			}
			T* s = (T *)bytes;

			return s;
		}
	};


}