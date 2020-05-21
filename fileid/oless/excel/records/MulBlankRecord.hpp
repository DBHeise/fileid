#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/a9ab7fa1-183a-487c-a506-6b4a19e770be
			// The MulBlank record specifies a series of blank cells in a sheet row. This record can store up to 256 IXFCell structures.
			class MulBlankRecord : public Record {
			private:
				unsigned short rw;
				unsigned short colFirst;
				unsigned short colLast;
				std::vector<unsigned short> rgixfe;

			public:

				MulBlankRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->rw = common::ReadUShort(buffer, max, index);
					index += 2;

					this->colFirst = common::ReadUShort(buffer, max, index);
					index += 2;

					this->colLast = common::ReadUShort(buffer, max, max - 4);

					unsigned int count = this->colLast - this->colFirst + 1;
					for (unsigned int i = 0; i < count; i++) {
						unsigned short tmp = common::ReadUShort(buffer, max, index);
						index += 2;
						this->rgixfe.push_back(tmp);
					}
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<rw>" << this->rw << "</rw>";
					str << "<colFirst>" << ColNumToName(this->colFirst) << "</colFirst>";
					str << "<colLast>" << ColNumToName(this->colLast) << "</colLast>";
					if (this->rgixfe.size() > 0) {
						str << "<rgixfe>";
						for (auto it = this->rgixfe.begin(); it != this->rgixfe.end(); it++) {
							str << "<ixfe>" << (*it) << "</ixfe>";
						}
						str << "</rgixfe>";
					}
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"rw\":" << this->rw;
					str << ",\"colFirst\":\"" << ColNumToName(this->colFirst) << "\"";
					str << ",\"colLast\":\"" << ColNumToName(this->colLast) << "\"";
					if (this->rgixfe.size() > 0) {
						str << ",\"rgixfe\":[" << common::vector_join(this->rgixfe, ",", false) << "]";
					}
					str << "}";
					return str.str();
				}

			};
		}
	}
}
