#pragma once

#include "../../IParsable.hpp"
#include "RgceElfLoc.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				class Ptg: public IParseable {
				public:
					virtual unsigned int size() const = 0;
					virtual std::string to_string() const = 0;
				};

				class PtgUnknown : public Ptg {
				private:
					unsigned char type;
					unsigned char subtype;
				public:
					PtgUnknown(unsigned char type, unsigned char subtype) : type(type), subtype(subtype) {};
					unsigned int size() const override { return 1; }
					std::string to_string() const override { return "UnknownPTG(type=" + std::to_string(this->type) + ",subType=" + std::to_string(this->subtype) + ")"; }

					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override { }
				};

				class PtgBasic : public Ptg {
				private:
					unsigned char ptg : 7;
					unsigned char reserved : 1;
				public:
					unsigned int size() const override { return 1; }
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = common::ExtractBits(buffer[offset], 7, 0);
						this->reserved = common::ExtractBits(buffer[offset], 1, 7);
					}
				};


				class PtgSubType : public Ptg {
				private:
					unsigned char ptg : 5;
					unsigned char type : 2;
					unsigned char reserved : 1;
				public:
					unsigned int size() const override { return 1; }
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = common::ExtractBits(buffer[offset], 5, 0);
						this->type = common::ExtractBits(buffer[offset], 2, 5);
						this->reserved = common::ExtractBits(buffer[offset], 1, 7);
					}
				};

				class PtgBasic_elf : public Ptg {
				private:
					unsigned char ptg;
					unsigned char eptg;
					RgceElfLoc loc;
				public:
					unsigned int size() const override { return 4; }
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						this->ptg = buffer[offset];
						this->eptg = buffer[offset + 1];
						this->loc.Parse(buffer, offset + 2, max);
					}
				};

				class PtgSubType_ixti : public PtgSubType {
				private:
					unsigned short ixti;
				public:
					unsigned int size() const override { return PtgSubType::size() + 2; }
					virtual void Parse(unsigned char* buffer, size_t max, unsigned int offset) override {
						PtgSubType::Parse(buffer, max, offset);
						this->ixti = buffer[offset + PtgSubType::size()];
					}
				};
			}
		}
	}
}