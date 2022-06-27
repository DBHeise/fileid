#pragma once

#include <map>
#include <stdexcept>
#include "../../oless/pole.h"
#include "../../common.hpp"
#include "../../oless/OleCommon.hpp"
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
			std::string error;

			ExcelExtensionInfo() : OLESSExtensionInfo() {
				this->Extension = "xls";
				this->Name = "Microsoft Office Excel Workbook";
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
				if (!this->error.empty()) {
					str << ", \"ERROR\": \"" << this->error << "\"";
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
				if (!this->error.empty()) {
					str << "<ERROR>" << this->error << "</ERROR>";
				}
				str << "</item>";
				return str.str();
			}
		};
	
		void Detailer(common::ExtensionInfo*& e, const std::string filename, const POLE::Storage* storage, const std::wstring streamName, const std::vector<uint8_t> stream) {
			auto p = new ParseEngine();
			auto xl = new ExcelExtensionInfo();
			try {
				p->ParseStream(stream);
			}
			catch (const std::exception& e) {
				xl->error = e.what();
			}
			catch (...) {
				xl->error = "Unhandled exception";
			}

			xl->global = p->global;
			xl->sheets = p->sheets;
			xl->Version = p->Version;
			xl->VersionName = p->VersionName;
			xl->SubType = p->SubType;

			e = xl;
		}
	}
}
