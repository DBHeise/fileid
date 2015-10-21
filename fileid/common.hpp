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

namespace common {

	std::vector<unsigned char> readFile(std::string file, unsigned int max) {
		std::vector<unsigned char> ans;
		std::ifstream stream(file, std::ios::binary|std::ios::ate);
		if (stream) {
			unsigned int fileSize = static_cast<unsigned int>(stream.tellg());
			stream.seekg(0, std::ios::beg);
			
			unsigned int size = max;
			if (fileSize < max) {
				size = fileSize;
			}
			ans.resize(size);
			stream.read(reinterpret_cast<char*>(ans.data()), size);
			stream.close();
		}
		return ans;
	}
	int ConvertToIntLE(unsigned char* block, int offset) {
		int ans = 0;
		ans = ((int)block[offset] << 24) | ((int)block[offset + 1] << 16) | ((int)block[offset + 2] << 8) | ((int)block[offset + 3]);
		return ans;
	}
	int ConvertToIntBE(unsigned char* block, int offset) {
		int ans = 0;
		ans = ((int)block[offset + 3] << 24) | ((int)block[offset + 2] << 16) | ((int)block[offset + 1] << 8) | ((int)block[offset]);
		return ans;
	}
	bool checkMagic(const unsigned char* actual, unsigned int actualLength, const unsigned char* expected, unsigned int expectedLength, unsigned int offset) {
		bool ans = true;

		unsigned int min = expectedLength;
		unsigned int max = actualLength;
		const unsigned char* minner = expected;
		const unsigned char* maxxer = actual;
		if (expectedLength > actualLength) {
			min = actualLength;
			max = expectedLength;
			minner = actual;
			maxxer = expected;
		}

		if (offset + min > max)
			return false;

		for (unsigned int i = offset; i < (min + offset) && ans; i++)
			ans &= maxxer[i] == minner[i - offset];

		return ans;
	}

	class IExportable {
	public:
		virtual std::string ToJson() = 0;
		virtual std::string ToXml() = 0;
		virtual std::string ToCsv() = 0;
		virtual std::string ToText() = 0;
	};

	class ExtensionInfo : public IExportable {
	public:
		std::string Extension;
		unsigned short Version;
		std::string VersionName;
	public:
		virtual std::string ToJson() {
			std::ostringstream str;
			str << "{ \"extension\" : \"" << this->Extension << "\"";
			if (this->Version > 0) {
				str << ", \"version\" : \"" << this->Version << "\"";
			}
			str << ", \"name\" : \"" << this->VersionName << "\"";
			str << "}";
			return str.str();
		}
		virtual std::string ToXml() {
			std::ostringstream str;
			str << "<item>";
			str << "<extension>" << this->Extension << "</extension>";
			if (this->Version > 0) {
				str << "<version>" << this->Version << "</version>";
			}
			str << "<name>" << this->VersionName << "</name>";
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() {
			std::ostringstream str;
			str << this->Extension << "\t" << this->Version << "\t" << this->VersionName;
			return str.str();
		}
		virtual std::string ToCsv() {
			std::ostringstream str;
			str << this->Extension << "," << this->Version << "," << this->VersionName;
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


	typedef struct MagicInfo {
		std::string Extension;
		std::string Name;
		std::string Version;
		unsigned int offset;
		unsigned int size;
		unsigned char* magic;
		std::string extraName;
		MagicInfo(const char* ext, const char* n, const char* ver, unsigned int offset, unsigned int size, unsigned char* m, const char* ename) {
			std::string t(ext);
			this->Extension = t;
			std::string n2(n);
			this->Name = n2;
			std::string v(ver);
			this->Version = v;
			this->offset = offset;
			this->size = size;
			this->magic = m;
			if (ename != NULL) {
				std::string e(ename);
				this->extraName = e;
			}
		}
	} MagicInfo;

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

	// taken from: http://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data/7776146#7776146
	void hexDump(const char *desc, const void *addr, size_t len) {
		size_t i;
		unsigned char buff[17];
		unsigned char *pc = (unsigned char*)addr;

		// Output description if given.
		if (desc != NULL)
			printf("%s:\n", desc);

		// Process every byte in the data.
		for (i = 0; i < len; i++) {
			// Multiple of 16 means new line (with line offset).

			if ((i % 16) == 0) {
				// Just don't print ASCII for the zeroth line.
				if (i != 0)
					printf("  %s\n", buff);

				// Output the offset.
				printf("  %04x ", static_cast<unsigned int>(i));
			}

			// Now the hex code for the specific character.
			printf(" %02x", pc[i]);

			// And store a printable ASCII character for later.
			if ((pc[i] < 0x20) || (pc[i] > 0x7e))
				buff[i % 16] = '.';
			else
				buff[i % 16] = pc[i];
			buff[(i % 16) + 1] = '\0';
		}

		// Pad out last line if not exactly 16 characters.
		while ((i % 16) != 0) {
			printf("   ");
			i++;
		}

		// And print the final ASCII bit.
		printf("  %s\n", buff);
	}


	std::string const base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

		static std::string JsonEscape(const std::string &source) {
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
					if (iscntrl(*c)) {
						std::ostringstream oss;
						oss << "\\u" << std::hex << std::uppercase << std::setfill('0')
							<< std::setw(4) << static_cast<int>(*c);
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

		static unsigned short GetItem2Byte(const unsigned char* data, unsigned int index) {
			return (data[index + 1] << 8) | data[index + 0];
		}
		static unsigned int GetItem4Byte(const unsigned char* data, unsigned int index) {
			return
				(((unsigned long long)data[index + 3]) << 32) |
				(((unsigned int)data[index + 2]) << 16) |
				(((unsigned int)data[index + 1]) << 8) |
				data[index + 0];
		}
		static std::string GetItemString(const unsigned char* data, unsigned int index, unsigned int length) {
			std::string str((char*)&data[index], (size_t)length);
			return str;
		}
		static std::wstring GetItemStringW(const unsigned char* data, unsigned int index, unsigned int length) {
			std::wstring str(reinterpret_cast<wchar_t*>(data[index]), (size_t)length / sizeof(wchar_t));
			return str;
		}

		static inline bool is_base64(unsigned char c) {
			return (isalnum(c) || (c == '+') || (c == '/'));
		}
		static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
			std::string ret;
			int i = 0;
			int j = 0;
			unsigned char char_array_3[3];
			unsigned char char_array_4[4];

			while (in_len--) {
				char_array_3[i++] = *(bytes_to_encode++);
				if (i == 3) {
					char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
					char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
					char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
					char_array_4[3] = char_array_3[2] & 0x3f;

					for (i = 0; (i < 4); i++)
						ret += base64_chars[char_array_4[i]];
					i = 0;
				}
			}

			if (i)
			{
				for (j = i; j < 3; j++)
					char_array_3[j] = '\0';

				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (j = 0; (j < i + 1); j++)
					ret += base64_chars[char_array_4[j]];

				while ((i++ < 3))
					ret += '=';

			}

			return ret;

		}
		static std::string base64_decode(std::string const& encoded_string) {
			size_t in_len = encoded_string.size();
			size_t i = 0;
			size_t j = 0;
			int in_ = 0;
			unsigned char char_array_4[4], char_array_3[3];
			std::string ret;

			while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
				char_array_4[i++] = encoded_string[in_]; in_++;
				if (i == 4) {
					for (i = 0; i < 4; i++)
						char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

					char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
					char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
					char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

					for (i = 0; (i < 3); i++)
						ret += char_array_3[i];
					i = 0;
				}
			}

			if (i) {
				for (j = i; j < 4; j++)
					char_array_4[j] = 0;

				for (j = 0; j < 4; j++)
					char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
			}

			return ret;
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
			std::cout << "<file>" << std::endl;
			std::cout << "\t<name>" << file << "</name>" << std::endl;
			std::cout << "\t<" << headerName << ">" << std::endl;
			for (it = summary.begin(); it != summary.end(); it++) {
				std::cout << "\t\t" << (*it)->ToXml() << std::endl;
			}
			std::cout << "\t</" << headerName << ">" << std::endl;
			std::cout << "</file>" << std::endl;
			break;
		case OutputFormat::JSON:
			std::cout << "{ \"name\" : \"" << helper::JsonEscape(file) << "\"," << std::endl;
			std::cout << "\t \"" << headerName << "\": [" << std::endl;
			for (it = summary.begin(); it != summary.end(); it++) {
				if (it != summary.begin()) {
					std::cout << "," << std::endl;
				}
				std::cout << "\t\t" << (*it)->ToJson() << std::endl;
			}
			std::cout << "\n\t]\n}" << std::endl;
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
