#pragma once

#include "Record.hpp"
#include "../structures/Cell.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e2fe0d8d-6b97-4223-b267-df0eddd8ee7d
			// The WinProtect record specifies whether the workbook windows can be resized or moved and whether the window state can be changed.
			class WinProtectRecord : public Record {
				unsigned short fLockWn;
			public:
				WinProtectRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->fLockWn = common::ReadUShort(buffer, max, index, true);
					index += 2;
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<fLockWn>" << this->fLockWn << "</fLockWn>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"fLockWn\":" << this->fLockWn;
					str << "}";
					return str.str();
				}

			};
		}
	}
}
