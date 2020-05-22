#pragma once

#include "../../IParsable.hpp"
#include "RgceElfLoc.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				//Ptg - base class for all "Parse Things" (see https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/e7625cc8-3da9-4154-b449-49cf1bbd9703)
				class Ptg: public IParseable {
				public:
					virtual std::string to_string() const = 0;					
				};

				class PtgUnknown : public Ptg {
				public:
					unsigned char type;
					unsigned char subtype;
					PtgUnknown(unsigned char type, unsigned char subtype) : type(type), subtype(subtype) {
						this->bytesRead = 0;
					};
					std::string to_string() const override { return "UnknownPTG(type=" + std::to_string(this->type) + ",subType=" + std::to_string(this->subtype) + ")"; }

					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override { }
				};

				class PtgBasic : public Ptg {
				public:
					unsigned char ptg : 7;
					unsigned char reserved : 1;
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = common::ExtractBits(buffer[offset], 7, 1);
						this->reserved = common::ExtractBits(buffer[offset], 1, 8);
						this->bytesRead = 1;
					}
				};


				class PtgSubType : public Ptg {
				public:
					unsigned char ptg : 5;
					unsigned char type : 2;
					unsigned char reserved : 1;
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = common::ExtractBits(buffer[offset], 5, 1);
						this->type = common::ExtractBits(buffer[offset], 2, 6);
						this->reserved = common::ExtractBits(buffer[offset], 1, 8);
						this->bytesRead = 1;
					}
				};

				class PtgBasic_elf : public Ptg {
				public:
					unsigned char ptg;
					unsigned char eptg;
					RgceElfLoc loc;
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = buffer[offset];
						this->eptg = buffer[offset + 1];
						this->loc.Parse(buffer, max, offset + 2);
						this->bytesRead = 6;
					}
				};

				class PtgSubType_ixti : public PtgSubType {
				public:
					unsigned short ixti;
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						unsigned int index = offset;
						PtgSubType::Parse(buffer, max, index);
						index += this->bytesRead;

						this->ixti = common::ReadUShort(buffer, max, index);
						index += 2;

						this->bytesRead = index - offset;
					}
				};
			}
		}
	}
}