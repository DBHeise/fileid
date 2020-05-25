#pragma once

#include <map>
#include "../pole.h"
#include "../../common.hpp"
#include "../OleCommon.hpp"
#include "MSExcel.common.hpp"
#include "SubStream.hpp"
#include "Sheet.hpp"
#include "records/Record.Parser.hpp"
#include "ParseEngine.hpp"

namespace oless {
	namespace excel {


		class ExcelExtensionInfo : public OLESSExtensionInfo {
		public:
			//Global SubStream
			SubStream* global;
			std::vector<Sheet> sheets;

			ExcelExtensionInfo() : OLESSExtensionInfo() {
				this->Extension = "xls";
				this->Name = "Microsoft Office Excel Workbook";
			}

			void ParseStream(POLE::Stream* workbookStream) {
				auto p = new ParseEngine();
				p->ParseStream(workbookStream);
				this->global = p->global;
				this->sheets = p->sheets;
				this->Version = p->Version;
				this->VersionName = p->VersionName;
				this->SubType = p->SubType;
			}

			virtual std::string ToJson() const override {
				std::ostringstream str;
				str << "{";
				str << this->buildBaseJson();
				if (this->global != nullptr) {
					str << ", \"globals\": { " << this->global->ToJson() << "}";
				}
				if (this->sheets.size() > 0) {
					str << ", \"sheets\": [";
					for (std::vector<Sheet>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {
						if (i != this->sheets.begin()) str << ",";
						str << (*i).ToJson();
					}
					str << "]";
				}
				str << "}";
				return str.str();
			}
			virtual std::string ToXml() const override {
				std::ostringstream str;
				str << "<item>";
				str << this->buildBaseXml();
				if (this->global != nullptr) {
					str << "<globals>";
					str << this->global->ToXml();
					str << "</globals>";
				}
				if (this->sheets.size() > 0) {
					str << "<sheets>";
					for (std::vector<Sheet>::const_iterator i = this->sheets.begin(); i != this->sheets.end(); i++) {
						str << (*i).ToXml();
					}
					str << "</sheets>";
				}
				str << "</item>";
				return str.str();
			}
		};
	}
}
