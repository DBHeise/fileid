#pragma once

#include <vector>
#include "../../../../common.hpp"
#include "../../IParsable.hpp"
#include "Ptgs.hpp"


namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {

				// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6cdf7d38-d08c-4e56-bd2f-6c82b8da752e
				// The Rgce structure specifies a set of Ptgs, laid out sequentially in the file.
				class Rgce : public IParseable {
				public:
					std::vector<oless::excel::structures::formulas::Ptg*> list;

					virtual void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) override {
						unsigned int index = offset;

						/*
						while (index < max) {
							Ptg* child = nullptr;

							unsigned char ptgType = buffer[index];

							switch (ptgType) {
							case 0x01: child = PtgExp::Parse(buffer, index, max); break;
							case 0x02: child = PtgTbl::Parse(buffer, index, max); break;
							case 0x03: child = PtgAdd::Parse(buffer, index, max); break;
							case 0x04: child = PtgSub::Parse(buffer, index, max); break;
							case 0x05: child = PtgMul::Parse(buffer, index, max); break;
							case 0x06: child = PtgDiv::Parse(buffer, index, max); break;
							case 0x07: child = PtgPower::Parse(buffer, index, max); break;
							case 0x08: child = PtgConcat::Parse(buffer, index, max); break;
							case 0x09: child = PtgLt::Parse(buffer, index, max); break;
							case 0x0A: child = PtgLe::Parse(buffer, index, max); break;
							case 0x0B: child = PtgEq::Parse(buffer, index, max); break;
							case 0x0C: child = PtgGe::Parse(buffer, index, max); break;
							case 0x0D: child = PtgGt::Parse(buffer, index, max); break;
							case 0x0E: child = PtgNe::Parse(buffer, index, max); break;
							case 0x0F: child = PtgIsect::Parse(buffer, index, max); break;
							case 0x10: child = PtgUnion::Parse(buffer, index, max); break;
							case 0x11: child = PtgRange::Parse(buffer, index, max); break;
							case 0x12: child = PtgUplus::Parse(buffer, index, max); break;
							case 0x13: child = PtgUminus::Parse(buffer, index, max); break;
							case 0x14: child = PtgPercent::Parse(buffer, index, max); break;
							case 0x15: child = PtgParen::Parse(buffer, index, max); break;
							case 0x16: child = PtgMissArg::Parse(buffer, index, max); break;
							case 0x17: child = PtgStr::Parse(buffer, index, max); break;
							case 0x18:
							{
								unsigned char subType = buffer[index + 1];
								index++;
								switch (subType) {
								case 0x01: child = PtgElfLel::Parse(buffer, index, max); break;
								case 0x02: child = PtgElfRw::Parse(buffer, index, max); break;
								case 0x03: child = PtgElfCol::Parse(buffer, index, max); break;
								case 0x06: child = PtgElfRwV::Parse(buffer, index, max); break;
								case 0x07: child = PtgElfColV::Parse(buffer, index, max); break;
								case 0x0A: child = PtgElfRadical::Parse(buffer, index, max); break;
								case 0x0B: child = PtgElfRadicalS::Parse(buffer, index, max); break;
								case 0x0D: child = PtgElfColS::Parse(buffer, index, max); break;
								case 0x0F: child = PtgElfColSV::Parse(buffer, index, max); break;
								case 0x10: child = PtgElfRadicalLel::Parse(buffer, index, max); break;
								case 0x1D: child = PtgSxName::Parse(buffer, index, max); break;
								default: child = new PtgUnknown(ptgType, subType); break;
								}
								break;
							}
							case 0x19:
							{
								unsigned char subType = buffer[index + 1];
								index++;
								switch (subType) {
								case 0x01: child = PtgAttrSemi::Parse(buffer, index, max); break;
								case 0x02: child = PtgAttrIf::Parse(buffer, index, max); break;
								case 0x04: child = PtgAttrChoose::Parse(buffer, index, max); break;
								case 0x08: child = PtgAttrGoto::Parse(buffer, index, max); break;
								case 0x10: child = PtgAttrSum::Parse(buffer, index, max); break;
								case 0x20:
								case 0x21:
									child = PtgAttrBaxcel::Parse(buffer, index, max); break;
								case 0x40: child = PtgAttrSpace::Parse(buffer, index, max); break;
								case 0x41: child = PtgAttrSpaceSemi::Parse(buffer, index, max); break;
								default: child = new PtgUnknown(ptgType, subType); break;
								}
								break;
							}
							case 0x1C: child = PtgErr::Parse(buffer, index, max); break;
							case 0x1D: child = PtgBool::Parse(buffer, index, max); break;
							case 0x1E: child = PtgInt::Parse(buffer, index, max); break;
							case 0x1F: child = PtgNum::Parse(buffer, index, max); break;
							case 0x20:
							case 0x40:
							case 0x60:
								child = PtgArray::Parse(buffer, index, max); break;
							case 0x21:
							case 0x41:
							case 0x61:
								child = PtgFunc::Parse(buffer, index, max); break;
							case 0x22:
							case 0x42:
							case 0x62:
								child = PtgFuncVar::Parse(buffer, index, max); break;
							case 0x23:
							case 0x43:
							case 0x63:
								child = PtgName::Parse(buffer, index, max); break;
							case 0x24:
							case 0x44:
							case 0x64:
								child = PtgRef::Parse(buffer, index, max); break;
							case 0x25:
							case 0x45:
							case 0x65:
								child = PtgArea::Parse(buffer, index, max); break;
							case 0x26:
							case 0x46:
							case 0x66:
								child = PtgMemArea::Parse(buffer, index, max); break;
							case 0x27:
							case 0x47:
							case 0x67:
								child = PtgMemErr::Parse(buffer, index, max); break;
							case 0x28:
							case 0x48:
							case 0x68:
								child = PtgMemNoMem::Parse(buffer, index, max); break;
							case 0x29:
							case 0x49:
							case 0x69:
								child = PtgMemFunc::Parse(buffer, index, max); break;
							case 0x2A:
							case 0x4A:
							case 0x6A:
								child = PtgRefErr::Parse(buffer, index, max); break;
							case 0x2B:
							case 0x4B:
							case 0x6B:
								child = PtgAreaErr::Parse(buffer, index, max); break;
							case 0x2C:
							case 0x4C:
							case 0x6C:
								child = PtgRefN::Parse(buffer, index, max); break;
							case 0x2D:
							case 0x4D:
							case 0x6D:
								child = PtgAreaN::Parse(buffer, index, max); break;
							case 0x39:
							case 0x59:
							case 0x79:
								child = PtgNameX::Parse(buffer, index, max); break;
							case 0x3A:
							case 0x5A:
							case 0x7A:
								child = PtgRef3d::Parse(buffer, index, max); break;
							case 0x3B:
							case 0x5B:
							case 0x7B:
								child = PtgArea3d::Parse(buffer, index, max); break;
							case 0x3C:
							case 0x5C:
							case 0x7C:
								child = PtgRefErr3d::Parse(buffer, index, max); break;
							case 0x3D:
							case 0x5D:
							case 0x7D:
								child = PtgAreaErr3d::Parse(buffer, index, max); break;

							default: child = new PtgUnknown(ptgType, 0); break;
							}

							index += child->size();
							list.push_back(child);
						}
						*/
						

						this->bytesRead = index - offset;
					}

					std::string ToFormulaString() {
						std::ostringstream ss;
						for (auto it = this->list.begin(); it != this->list.end(); it++) {
							if (it != this->list.begin()) { ss << ";"; }
							ss << (*it)->to_string();
						}
						return ss.str();
					}
				};
			}
		}
	}
}
