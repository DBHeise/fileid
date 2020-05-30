#pragma once

#include "Record.hpp"

namespace oless {
	namespace excel {
		namespace records {

			class RowRecord : public Record {
			private:
				unsigned short rw;
				unsigned short colMic;
				unsigned short colMac;
				unsigned short miyRw;
				unsigned short reserved1;
				unsigned short unused1;

				unsigned short iOutlevel : 3;
				unsigned short reserved2 : 1;
				unsigned short fCollapsed : 1;
				unsigned short fDyZero : 1;
				unsigned short fUnsynced : 1;
				unsigned short fGhostDirty : 1;

				unsigned short reserved3;

				unsigned short ixfe_val : 12;
				unsigned short fExAsc : 1;
				unsigned short fExDes : 1;
				unsigned short fPhonetic : 1;
				unsigned short unused : 1;

			public:
				RowRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					unsigned int index = 0;
					auto buffer = this->Data.data();
					auto max = this->Data.size();

					this->rw = common::ReadUShort(buffer, max, index);
					index += 2;

					this->colMic = common::ReadUInt(buffer, max, index);
					index += 2;

					this->colMac = common::ReadUInt(buffer, max, index);
					index += 2;

					this->miyRw = common::ReadUInt(buffer, max, index);
					index += 2;

					this->reserved1 = common::ReadUInt(buffer, max, index);
					index += 2;

					this->unused1 = common::ReadUInt(buffer, max, index);
					index += 2;

					this->iOutlevel = common::ExtractBits(buffer[index], 3, 1);
					this->reserved2 = common::ExtractBits(buffer[index], 1, 4);
					this->fCollapsed = common::ExtractBits(buffer[index], 1, 5);
					this->fDyZero = common::ExtractBits(buffer[index], 1, 6);
					this->fUnsynced = common::ExtractBits(buffer[index], 1, 7);
					this->fGhostDirty = common::ExtractBits(buffer[index], 1, 8);
					index++;

					this->reserved3 = buffer[index];
					index++;

					this->ixfe_val = common::ReadUShort(buffer, max, index) >> 4;
					index++;

					this->fExAsc = common::ExtractBits(buffer[index], 1, 5);
					this->fExDes = common::ExtractBits(buffer[index], 1, 6);
					this->fPhonetic = common::ExtractBits(buffer[index], 1, 7);
					this->unused = common::ExtractBits(buffer[index], 1, 8);
				}

				virtual std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "<rw>" << this->rw << "</rw>";
					str << "<colMic>" << this->colMic << "</colMic>";
					str << "<colMac>" << this->colMac << "</colMac>";
					str << "<miyRw>" << this->miyRw << "</miyRw>";
					str << "<reserved1>" << this->reserved1 << "</reserved1>";
					str << "<unused1>" << this->unused1 << "</unused1>";
					str << "<iOutlevel>" << this->iOutlevel << "</iOutlevel>";
					str << "<reserved2>" << this->reserved2 << "</reserved2>";
					str << "<fCollapsed>" << this->fCollapsed << "</fCollapsed>";
					str << "<fDyZero>" << this->fDyZero << "</fDyZero>";
					str << "<fUnsynced>" << this->fUnsynced << "</fUnsynced>";
					str << "<fGhostDirty>" << this->fGhostDirty << "</fGhostDirty>";
					str << "<reserved3>" << this->reserved3 << "</reserved3>";
					str << "<ixfe_val>" << this->ixfe_val << "</ixfe_val>";
					str << "<fExAsc>" << this->fExAsc << "</fExAsc>";
					str << "<fExDes>" << this->fExDes << "</fExDes>";
					str << "<fPhonetic>" << this->fPhonetic << "</fPhonetic>";
					str << "<unused>" << this->unused << "</unused>";
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << ",\"rw\":" << this->rw;
					str << ",\"colMic\":" << this->colMic;
					str << ",\"colMac\":" << this->colMac;
					str << ",\"miyRw\":" << this->miyRw;
					str << ",\"reserved1\":" << this->reserved1;
					str << ",\"unused1\":" << this->unused1;
					str << ",\"iOutlevel\":" << this->iOutlevel;
					str << ",\"reserved2\":" << this->reserved2;
					str << ",\"fCollapsed\":" << this->fCollapsed;
					str << ",\"fDyZero\":" << this->fDyZero;
					str << ",\"fUnsynced\":" << this->fUnsynced;
					str << ",\"fGhostDirty\":" << this->fGhostDirty;
					str << ",\"reserved3\":" << this->reserved3;
					str << ",\"ixfe_val\":" << this->ixfe_val;
					str << ",\"fExAsc\":" << this->fExAsc;
					str << ",\"fExDes\":" << this->fExDes;
					str << ",\"fPhonetic\":" << this->fPhonetic;
					str << ",\"unused\":" << this->unused;

					str << "}";
					return str.str();
				}
			};
		}
	}
}
