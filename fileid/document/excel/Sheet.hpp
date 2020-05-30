#pragma once

#include <string>
#include <sstream>

#include "MSExcel.common.hpp"
#include "SubStream.hpp"
#include "records/Record.hpp"

namespace oless {
	namespace excel {

		class Sheet {
		private:
			SubStream children;

		public:
			std::string		Name;
			unsigned short	Visiblity;
			unsigned short  Type;
			unsigned int    Offset;
			
			Sheet() : Name{ "" }, Visiblity(0), Type(0), Offset(0) {}

			void AddRecord(records::Record* r) {
				this->children.AddRecord(r);
			}
			
			std::string ToXml() const
			{
				std::ostringstream str;
				str << "<Sheet>";
				str << "<Name>" << common::XmlEscape(this->Name) << "</Name>";
				str << "<Type>" << GetSheetTypeStr(this->Type) << "</Type>";
				str << "<Visiblity>" << GetVisibilityStr(this->Visiblity) << "</Visiblity>";
				str << "<Offset>" << this->Offset << "</Offset>";
				if (this->children.size() > 0) {
					str << this->children.ToXml();
				}
				str << "</Sheet>";
				return str.str();
			}
			std::string ToJson() const
			{
				std::ostringstream str;
				str << "{";
				str << "\"Name\":\"" << common::JsonEscape(this->Name) << "\",";
				str << "\"Type\":\"" << GetSheetTypeStr(this->Type) << "\",";
				str << "\"Visiblity\":\"" << GetVisibilityStr(this->Visiblity) << "\",";
				str << "\"Offset\":" << this->Offset;
				if (this->children.size() > 0) {
					str << ",";
					str << this->children.ToJson();
				}
				str << "}";
				return str.str();
			}
		};


	}
}