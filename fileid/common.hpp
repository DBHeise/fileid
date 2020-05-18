#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <set>
#include <cstring>
#include <cstdio>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <chrono>
#include <fstream>

#define STD_BUFFER_SIZE 512


namespace common {

	//displayDuration - turns a FILETIME into a duration string (i.e. HH:MM:SS)
	std::string displayDuration(unsigned long long filetime) {
		using namespace std::chrono;
		
		microseconds micro(filetime/10);
		auto ms = duration_cast<milliseconds>(micro);
		micro -= duration_cast<microseconds>(ms);
		auto secs = duration_cast<seconds>(ms);
		ms -= duration_cast<milliseconds>(secs);
		auto mins = duration_cast<minutes>(secs);
		secs -= duration_cast<seconds>(mins);
		auto hour = duration_cast<hours>(mins);
		mins -= duration_cast<minutes>(hour);		

		std::ostringstream str;
		str << std::setfill('0') << std::setw(2) << hour.count();
		str << ":";
		str << std::setfill('0') << std::setw(2) << mins.count();
		str << ":";
		str << std::setfill('0') << std::setw(2) << secs.count();
		if (ms.count() > 0 || micro.count() > 0) {
			str << "." << std::setfill('0') << std::setw(3) << ms.count();
			str << std::setfill('0') << std::setw(3) << micro.count();
		}
		return str.str();
	}

	//convertFILETIME - converts a FILETIME to unix seconds
	time_t convertFILETIME(unsigned long long time) {
		return (time_t)((time / 10000000) - 11644473600LL);
	}

	//FileTimeToString - turns a FILETIME into a human readable ISO8601 string
	std::string FileTimeToString(unsigned long long time) {		
		time_t t = convertFILETIME(time);
		if (t > 0) {
			struct tm dt;
			char buffer[STD_BUFFER_SIZE] = { 0 };			
#ifdef WIN32
			localtime_s(&dt, &t);
#else
			localtime_r(&t, &dt);
#endif
			strftime(buffer, STD_BUFFER_SIZE, "%F %T", &dt);
			return std::string(buffer);
		}
		return "1601-01-01 00:00:00";
	}

	//iequals - compares two string in case-insensitive manner
	// taken from: https://stackoverflow.com/a/4119881/13124
	bool iequals(const std::string& a, const std::string& b)
	{
		return std::equal(a.begin(), a.end(),
			b.begin(), b.end(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});
	}
	//iequals - compares two strings in a case-insensitive manner
	// modified to take std::wstring
	bool iequals(const std::wstring& a, const std::wstring& b)
	{
		return std::equal(a.begin(), a.end(),
			b.begin(), b.end(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});
	}

	//ltrim - left trim of given characters
	// taken from:http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
	std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		str.erase(0, str.find_first_not_of(chars));
		return str;
	}

	//rtrim - right trim of given characters
	// taken from:http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
	std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		str.erase(str.find_last_not_of(chars) + 1);
		return str;
	}

	//trim - right trim followed by left trim
	// taken from:http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
	std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
	{
		return ltrim(rtrim(str, chars), chars);
	}

	//erasenulls - removes null characters from std::string
	std::string erasenulls(std::string str) {
		str.erase(std::find(str.begin(), str.end(), '\0'), str.end());
		return str;
	}

	//convert - Converts a wstring to a string
	// taken from: https://stackoverflow.com/a/18374698/13124
	std::string convert(std::wstring str) {
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string converted_str = converter.to_bytes(str);
		return converted_str;
	}


	//bin2hex11 - Outputs the bytes in a HEX string 
	std::string bin2hex11(const unsigned char* buffer, unsigned int size) {
		std::ostringstream oss;
		oss << std::setfill('0');
		for (size_t i = 0; i < size; i++)
		{
			oss << std::hex << std::setw(2) << buffer[i];
		}
		return oss.str();

	}

	//bin2hex11 - Outputs the vector in a HEX string
	// taken from: https://stackoverflow.com/a/14826747/13124
	std::string bin2hex11(const std::vector<unsigned char>& buffer)
	{
		std::ostringstream oss;
		oss << std::setfill('0');
		std::for_each(buffer.begin(), buffer.end(),
			[&oss](unsigned char ch)
			{
				oss << std::hex
					<< std::setw(2)
					<< static_cast<int>(ch);
			});
		return oss.str();
	}

	//readBuffer - reads data into a std::vector
	std::vector<unsigned char> readBuffer(unsigned char* buffer, std::size_t size) {
		std::vector<unsigned char> tmp;
		tmp.reserve(size);
		std::copy(buffer, buffer + size, std::back_inserter(tmp));
		return tmp;
	}

	//getFileSize - gets the size of a file by opening it and seeking to the end
	unsigned int getFileSize(std::string file) {
		std::ifstream ifs;
		ifs.open(file, std::ios::binary);
		ifs.seekg(0, std::ios::end);
		auto pos = ifs.tellg();
		ifs.close();
		return (unsigned int)pos;
	}

	//readFile - reads 'max' bytes from file into std::vector
	std::vector<unsigned char> readFile(std::string file, std::size_t max) {
		std::vector<unsigned char> ans;
		std::ifstream stream(file, std::ios::binary | std::ios::ate);
		if (stream) {
			unsigned int fileSize = static_cast<unsigned int>(stream.tellg());
			stream.seekg(0, std::ios::beg);

			std::size_t size = max;
			if (fileSize < max) {
				size = fileSize;
			}
			ans.resize(size);
			stream.read(reinterpret_cast<char*>(ans.data()), size);
			stream.close();
		}
		return ans;
	}

	//ExtractBits - extracts a single bit from a single byte number, offset is 1-based
	unsigned char ExtractBits(unsigned char num, unsigned short bitCount, unsigned short bitOffset) {
		return ((1 << bitCount) - 1) & (num >> (bitOffset - 1));
	}

	//VerifyGuids - compares two guids in thier raw-array form
	bool VerifyGuids(const unsigned char actual[16], const unsigned char expected[16]) {
		bool ans = true;
		for (int i = 0; ans && i < 16; i++)
		{
			ans &= actual[i] == expected[i];
		}
		return ans;
	}

	//ReadUShort - reads a two-byte unsigned short
	unsigned short ReadUShort(const unsigned char* buffer, std::size_t max, const unsigned int offset, bool bigEndian = false) {
		unsigned short ans = 0;
		if (offset + 1 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		if (bigEndian) {
			ans = ((unsigned short)buffer[offset] << 8) | ((unsigned short)buffer[offset + 1]);
		}
		else {
			ans = ((unsigned short)buffer[offset + 1] << 8) | ((unsigned short)buffer[offset]);
		}
		return ans;
	}

	//ReadSShort - reads a two-byte signed short
	signed short ReadSShort(const unsigned char* buffer, std::size_t max, const unsigned int offset, bool bigEndian = false) {
		signed short ans = 0;
		if (offset + 1 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		if (bigEndian) {
			ans = ((signed short)buffer[offset] << 8) | ((signed short)buffer[offset + 1]);
		}
		else {
			ans = ((signed short)buffer[offset + 1] << 8) | ((signed short)buffer[offset]);
		}
		return ans;
	}

	//ReadUInt - reads a four-byte unsigned int
	unsigned int ReadUInt(const unsigned char* buffer, std::size_t max, const unsigned int offset, bool bigEndian = false) {
		unsigned int ans = 0;
		if (offset + 3 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		if (bigEndian) {
			ans = (((unsigned long long)buffer[offset + 3]) << 24) |
				(((unsigned long)buffer[offset + 2]) << 16) |
				(((unsigned long)buffer[offset + 1]) << 8) |
				(unsigned int)buffer[offset + 0];
		}
		else {
			ans = (((unsigned long long)buffer[offset]) << 24) |
				(((unsigned long)buffer[offset + 1]) << 16) |
				(((unsigned long)buffer[offset + 2]) << 8) |
				(unsigned int)buffer[offset + 3];
		}
		return ans;
	}
	
	//ReadSInt - reads a four-byte signed int
	signed int ReadSInt(const unsigned char* buffer, std::size_t max, const unsigned int offset, bool bigEndian = false) {
		signed int ans = 0;
		if (offset + 3 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		if (bigEndian) {
			ans = (((signed long long)buffer[offset + 3]) << 24) |
				(((signed long)buffer[offset + 2]) << 16) |
				(((signed long)buffer[offset + 1]) << 8) |
				(signed int)buffer[offset + 0];
		}
		else {
			ans = (((signed long long)buffer[offset]) << 24) |
				(((signed long)buffer[offset + 1]) << 16) |
				(((signed long)buffer[offset + 2]) << 8) |
				(signed int)buffer[offset + 3];
		}
		return ans;
	}

	
	unsigned long ReadULong(const unsigned char* buffer, std::size_t max, const unsigned int offset) {
		if (offset + sizeof(unsigned long) > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		struct tmp {
			unsigned long v;
		};
		auto t = reinterpret_cast<tmp*>(const_cast<unsigned char*>(buffer) + offset);
		return t->v;
	}

	//ReadULongLong - reads a 8-byte unsigned long long
	unsigned long long ReadULongLong(const unsigned char* buffer, std::size_t max, const unsigned int offset) {
		if (offset + sizeof(unsigned long long) > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		struct tmp {
			unsigned long long v;
		};
		auto t = reinterpret_cast<tmp*>(const_cast<unsigned char*>(buffer) + offset);
		return t->v;
	}

	//ReadString - reads in a string
	std::string ReadString(const unsigned char* buffer, std::size_t max, unsigned int offset, unsigned int strLength) {
		if (offset + strLength > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		std::string str((char*)&buffer[offset], (size_t)strLength);
		return str;
	}

	//ReadWString - reads in a wide string (where strLength is the number of bytes)
	std::wstring ReadWString(const unsigned char* buffer, std::size_t max, unsigned int offset, unsigned int strLength) {
		if (offset + strLength > max) {
			throw std::range_error("Offset would read past end of buffer");
		}

		std::wstring str((wchar_t*)&buffer[offset], (wchar_t*)&buffer[offset+strLength]);
		return str;
	}

	//ReadFloat = reads an 4-byte (single precision) IEEE floating-point number
	float ReadFloat(const unsigned char* buffer, std::size_t max, const unsigned int offset) {
		struct tmp {
			float v;
		};
		if (offset + 4 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		auto t = reinterpret_cast<tmp*>(const_cast<unsigned char*>(buffer) + offset);
		return t->v;
	}

	//ReadDouble = reads an 8-byte (double precision) IEEE floating-point number
	double ReadDouble(const unsigned char* buffer, std::size_t max, const unsigned int offset) {
		struct tmp {
			double v;
		};
		if (offset + 8 > max) {
			throw std::range_error("Offset would read past end of buffer");
		}
		auto t = reinterpret_cast<tmp*>(const_cast<unsigned char*>(buffer) + offset);
		return t->v;
	}

	//checkMagic - checks one buffer against another buffer
	bool checkMagic(const unsigned char* actual, std::size_t actualLength, const unsigned char* expected, std::size_t expectedLength, unsigned int offset) {
		bool ans = true;

		auto min = expectedLength;
		auto max = actualLength;
		auto minner = expected;
		auto maxxer = actual;
		if (expectedLength > actualLength) {
			min = actualLength;
			max = expectedLength;
			minner = actual;
			maxxer = expected;
		}

		if (offset + min > max || actualLength < expectedLength)
			return false;

		for (std::size_t i = offset; i < (min + offset) && ans; i++)
			ans &= maxxer[i] == minner[i - offset];

		return ans;
	}

	//JsonEscape - escapes a string to be safe for JSON
	static std::string JsonEscape(const std::string& source) {
		std::string result;
		for (const char* c = source.c_str(); *c != 0; ++c) {
			switch (*c) {
			case '\"':
				result += "\\\"";
				break;
			case '\\':
				result += "\\\\";
				break;
			case '\b':
				result += "\\b";
				break;
			case '\f':
				result += "\\f";
				break;
			case '\n':
				result += "\\n";
				break;
			case '\r':
				result += "\\r";
				break;
			case '\t':
				result += "\\t";
				break;
			default:
				unsigned char ci = static_cast<unsigned char>(*c);
				if (iscntrl(ci) || ci > 127) {
					std::ostringstream oss;
					oss << "\\u" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << ((static_cast<unsigned int>(*c) << 24) >> 24); //ugh!
					result += oss.str();
				}
				else {
					result += *c;
				}
				break;
			}
		}
		return result;
	}

	class IExportable {
	public:
		virtual std::string ToJson() const = 0;
		virtual std::string ToXml() const = 0;
		virtual std::string ToCsv() const = 0;
		virtual std::string ToText() const = 0;
	};

	class ExtensionInfo : public IExportable {
	protected:
		virtual std::string buildBaseJson() const {
			std::ostringstream str;
			str << "\"extension\" : \"" << this->Extension << "\"";
			if (this->Name.size() > 0) {
				str << ", \"name\":\"" << this->Name << "\"";
			}
			if (this->SubType.size() > 0) {
				str << ", \"subtype\":\"" << common::JsonEscape(this->SubType) << "\"";
			}
			if (this->Version > 0) {
				str << ", \"version\" : \"" << this->Version << "\"";
			}
			if (this->VersionName.size() > 0) {
				str << ", \"versionname\" : \"" << this->VersionName << "\"";
			}
			return str.str();
		}
		virtual std::string buildBaseXml() const {
			std::ostringstream str;
			str << "<extension>" << this->Extension << "</extension>";
			if (this->Name.size() > 0) {
				str << "<name>" << this->Name << "</name>";
			}
			if (this->SubType.size() > 0) {
				str << "<subtype>" << this->SubType << "</subtype>";
			}
			if (this->Version > 0) {
				str << "<version>" << this->Version << "</version>";
			}
			if (this->VersionName.size() > 0) {
				str << "<versionname>" << this->VersionName << "</versionname>";
			}
			return str.str();
		}
	public:
		std::string Extension;
		std::string Name;
		std::string SubType;
		unsigned short Version;
		std::string VersionName;
	public:
		ExtensionInfo() {
			this->Version = 0;
		}
		bool operator==(const ExtensionInfo* other) const {
			return this->Extension.compare(other->Extension) == 0;
		}
		bool operator!=(const ExtensionInfo* other) const {
			return this->Extension.compare(other->Extension) != 0;
		}
		virtual std::string ToJson() const {
			std::ostringstream str;
			str << "{";
			str << this->buildBaseJson();
			str << "}";
			return str.str();
		}
		virtual std::string ToXml() const {
			std::ostringstream str;
			str << "<item>";
			str << this->buildBaseXml();
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() const {
			std::ostringstream str;
			str << this->Extension;
			str << "\t" << this->Name;
			str << "\t" << this->SubType;
			str << "\t" << this->Version;
			str << "\t" << this->VersionName;
			return str.str();
		}
		virtual std::string ToCsv() const {
			std::ostringstream str;
			str << this->Extension;
			str << "," << this->Name;
			str << "," << this->SubType;
			str << "," << this->Version;
			str << "," << this->VersionName;
			return str.str();
		}
	};

	enum OutputFormat {
		TEXT,
		JSON,
		XML,
		CSV
	};

	// Extra Information Functions
	typedef std::vector<ExtensionInfo*>(*ExtraDataFunc)(const std::string, std::vector<unsigned char>);


	struct MagicInfo {
		std::string Extension;
		std::string Name;
		std::string Version;
		unsigned int offset;
		unsigned int size;
		unsigned char* magic;
		ExtraDataFunc extraFunc;
		MagicInfo(const char* ext, const char* n, const char* ver, unsigned int offset, unsigned int size, unsigned char* m, ExtraDataFunc ename) {
			std::string t(ext);
			this->Extension = t;
			std::string n2(n);
			this->Name = n2;
			std::string v(ver);
			this->Version = v;
			this->offset = offset;
			this->size = size;
			this->magic = m;
			if (ename != nullptr) {
				this->extraFunc = ename;
			}
		}
	};

	OutputFormat ParseOutputFormat(std::string input) {
		std::unordered_map<std::string, OutputFormat> map = {
			{ "xml", OutputFormat::XML },
			{ "csv", OutputFormat::CSV },
			{ "txt", OutputFormat::TEXT },
			{ "json",OutputFormat::JSON }
		};
		std::unordered_map<std::string, OutputFormat>::const_iterator got = map.find(input);
		if (got == map.end()) {
			return OutputFormat::TEXT;
		}
		else {
			return got->second;
		}
	}


	class helper
	{

	public:
		helper() {}
		~helper() {}


		template<class T>
		static std::string vector_join(const std::vector<T>& v, const std::string& token, const bool useQuotes = false) {
			std::ostringstream result;
			for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); i++) {
				if (i != v.begin()) result << token;
				if (useQuotes)
					result << "\"" << *i << "\"";
				else
					result << *i;
			}
			return result.str();
		}
	};

	template<class T>
	void Output(OutputFormat format, std::string file, std::string headerName, std::vector<T*> summary) {
		typename std::vector<T*>::iterator it;
		switch (format) {
		case OutputFormat::TEXT:
			std::cout << file << std::endl;
			for (it = summary.begin(); it != summary.end(); it++) {
				std::cout << "\t" << (*it)->ToText() << std::endl;
			}
			break;
		case OutputFormat::XML:
			std::cout << "<file>";
			std::cout << "<name>" << file << "</name>";
			std::cout << "<" << headerName << ">";
			for (it = summary.begin(); it != summary.end(); it++) {
				std::cout << (*it)->ToXml();
			}
			std::cout << "</" << headerName << ">";
			std::cout << "</file>";
			break;
		case OutputFormat::JSON:
			std::cout << "{\"name\":\"" << common::JsonEscape(file) << "\",";
			std::cout << "\"" << headerName << "\":[";
			for (it = summary.begin(); it != summary.end(); it++) {
				if (it != summary.begin()) {
					std::cout << ",";
				}
				std::cout << (*it)->ToJson();
			}
			std::cout << "]}";
			break;
			break;
		case OutputFormat::CSV:
			for (it = summary.begin(); it != summary.end(); it++) {
				std::cout << (*it)->ToCsv() << std::endl;
			}
			break;
		default:
			std::cout << "Unknown Output Format!" << std::endl;
		}
	}
}
