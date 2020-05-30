#pragma once
#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class BoundSheet5Record : public Record {
			private:
				unsigned int lblPlyPos;
				unsigned char hsState : 2;
				unsigned char unused : 6;
				unsigned char dt;

			public:
				std::string Name;

				BoundSheet5Record(unsigned short type, std::vector<uint8_t> data) : Record(type, data)
				{
					auto buffer = this->Data.data();
					auto max = this->Data.size();
					unsigned int index = 0;

					this->lblPlyPos = common::ReadUInt(buffer, max, index, true);
					index += 4;

					this->hsState = common::ExtractBits(buffer[index], 2, 1);
					this->unused = common::ExtractBits(buffer[index], 6, 3);
					index++;

					this->dt = buffer[index];
					index++;

					unsigned char cch = buffer[index];
					index++;

					std::string tmpName(reinterpret_cast<char const*>(buffer + index), cch);
					this->Name = tmpName;
					index += cch;
				}
			};
		}
	}
}