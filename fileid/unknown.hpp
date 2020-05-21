#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "common.hpp"

class UnknownExtensionInfo : public common::ExtensionInfo {
private:
	std::vector<unsigned char> sample;
	std::string sampleStr;
public:
	UnknownExtensionInfo(std::vector<unsigned char> buffer) {
		this->sample = buffer;
		std::string tmpStr(reinterpret_cast<char*>(&this->sample[0]), this->sample.size());
		this->sampleStr = tmpStr;
		this->Extension = "unknown";
		this->VersionName = "Unknown File";
	}
	virtual std::string ToJson() const override {
		std::ostringstream str;
		str << "{";
		str << "\"extension\" : \"" << this->Extension << "\"";
		str << ", \"name\" : \"" << this->VersionName << "\"";		
		str << ", \"sampleStr\":\"" << common::JsonEscape(this->sampleStr) << "\"";
		str << ", \"sampleHex\":\"" << common::bin2hex11(this->sample) << "\"";
		str << "}";
		return str.str();
	}
	virtual std::string ToXml() const override {
		std::ostringstream str;
		str << "<item>";
		str << "<extension>" << this->Extension << "</extension>";
		str << "<name>" << this->VersionName << "</name>";		
		str << "<sampleStr><![CDATA[" << common::XmlEscape(this->sampleStr) << "]]></sampleStr>";
		str << "<sampleHex>" << common::bin2hex11(this->sample) << "</sampleHex>";
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