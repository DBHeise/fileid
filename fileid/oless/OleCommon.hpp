#pragma once
#include <string>
#include <ostream>
#include <sstream>
#include "..\common.hpp"

namespace OleStructuredStorage {
	class OleSummary : public common::IExportable {
	public:
		std::string FullName;
		unsigned long long Size;

		virtual std::string ToJson() {
			std::ostringstream str;
			str << "{ \"path\" : \"" << common::helper::JsonEscape(this->FullName) << "\", \"size\" : \"" << this->Size << "\"}";
			return str.str();
		}
		virtual std::string ToXml() {
			std::ostringstream str;
			str << "<item>";
			str << "<path>" << this->FullName << "</path>";
			str << "<size>" << this->Size << "</size>";
			str << "</item>";
			return str.str();
		}
		virtual std::string ToText() {
			std::ostringstream str;
			str << this->FullName << "\t" << this->Size;
			return str.str();
		}
		virtual std::string ToCsv() {
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
				throw std::exception("WTF");
			}
			T* s = (T *)bytes;

			return s;
		}
	};


}