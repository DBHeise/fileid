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
				class Rgce {
				public:
					std::vector<oless::excel::structures::formulas::Ptg*> list;
					unsigned int bytesRead;

					void Parse(unsigned char* buffer, std::size_t max, unsigned int offset) {
						unsigned int index = offset;
						
						while (index < max) {
							Ptg* child = nullptr;

							unsigned char ptgType = buffer[index];

							switch (ptgType) {
							case 0x01: child = new PtgExp(buffer, max, index); break;
							case 0x02: child = new PtgTbl(buffer, max, index); break;
							case 0x03: child = new PtgAdd(buffer, max, index); break;
							case 0x04: child = new PtgSub(buffer, max, index); break;
							case 0x05: child = new PtgMul(buffer, max, index); break;
							case 0x06: child = new PtgDiv(buffer, max, index); break;
							case 0x07: child = new PtgPower(buffer, max, index); break;
							case 0x08: child = new PtgConcat(buffer, max, index); break;
							case 0x09: child = new PtgLt(buffer, max, index); break;
							case 0x0A: child = new PtgLe(buffer, max, index); break;
							case 0x0B: child = new PtgEq(buffer, max, index); break;
							case 0x0C: child = new PtgGe(buffer, max, index); break;
							case 0x0D: child = new PtgGt(buffer, max, index); break;
							case 0x0E: child = new PtgNe(buffer, max, index); break;
							case 0x0F: child = new PtgIsect(buffer, max, index); break;
							case 0x10: child = new PtgUnion(buffer, max, index); break;
							case 0x11: child = new PtgRange(buffer, max, index); break;
							case 0x12: child = new PtgUplus(buffer, max, index); break;
							case 0x13: child = new PtgUminus(buffer, max, index); break;
							case 0x14: child = new PtgPercent(buffer, max, index); break;
							case 0x15: child = new PtgParen(buffer, max, index); break;
							case 0x16: child = new PtgMissArg(buffer, max, index); break;
							case 0x17: child = new PtgStr(buffer, max, index); break;
							case 0x18:
							{
								unsigned char subType = buffer[index + 1];
								switch (subType) {
								case 0x01: child = new PtgElfLel(buffer, max, index); break;
								case 0x02: child = new PtgElfRw(buffer, max, index); break;
								case 0x03: child = new PtgElfCol(buffer, max, index); break;
								case 0x06: child = new PtgElfRwV(buffer, max, index); break;
								case 0x07: child = new PtgElfColV(buffer, max, index); break;
								case 0x0A: child = new PtgElfRadical(buffer, max, index); break;
								case 0x0B: child = new PtgElfRadicalS(buffer, max, index); break;
								case 0x0D: child = new PtgElfColS(buffer, max, index); break;
								case 0x0F: child = new PtgElfColSV(buffer, max, index); break;
								case 0x10: child = new PtgElfRadicalLel(buffer, max, index); break;
								case 0x1D: child = new PtgSxName(buffer, max, index); break;
								default: child = new PtgUnknown(ptgType, subType); break;
								}
								break;
							}
							case 0x19:
							{
								unsigned char subType = buffer[index + 1];								
								switch (subType) {
								case 0x01: child = new PtgAttrSemi(buffer, max, index); break;
								case 0x02: child = new PtgAttrIf(buffer, max, index); break;
								case 0x04: child = new PtgAttrChoose(buffer, max, index); break;
								case 0x08: child = new PtgAttrGoto(buffer, max, index); break;
								case 0x10: child = new PtgAttrSum(buffer, max, index); break;
								case 0x20:
								case 0x21:
									child = new PtgAttrBaxcel(buffer, max, index); break;
								case 0x40: child = new PtgAttrSpace(buffer, max, index); break;
								case 0x41: child = new PtgAttrSpaceSemi(buffer, max, index); break;
								default: child = new PtgUnknown(ptgType, subType); break;
								}
								break;
							}
							case 0x1C: child = new PtgErr(buffer, max, index); break;
							case 0x1D: child = new PtgBool(buffer, max, index); break;
							case 0x1E: child = new PtgInt(buffer, max, index); break;
							case 0x1F: child = new PtgNum(buffer, max, index); break;
							case 0x20:
							case 0x40:
							case 0x60:
								child = new PtgArray(buffer, max, index); break;
							case 0x21:
							case 0x41:
							case 0x61:
								child = new PtgFunc(buffer, max, index); break;
							case 0x22:
							case 0x42:
							case 0x62:
								child = new PtgFuncVar(buffer, max, index); break;
							case 0x23:
							case 0x43:
							case 0x63:
								child = new PtgName(buffer, max, index); break;
							case 0x24:
							case 0x44:
							case 0x64:
								child = new PtgRef(buffer, max, index); break;
							case 0x25:
							case 0x45:
							case 0x65:
								child = new PtgArea(buffer, max, index); break;
							case 0x26:
							case 0x46:
							case 0x66:
								child = new PtgMemArea(buffer, max, index); break;
							case 0x27:
							case 0x47:
							case 0x67:
								child = new PtgMemErr(buffer, max, index); break;
							case 0x28:
							case 0x48:
							case 0x68:
								child = new PtgMemNoMem(buffer, max, index); break;
							case 0x29:
							case 0x49:
							case 0x69:
								child = new PtgMemFunc(buffer, max, index); break;
							case 0x2A:
							case 0x4A:
							case 0x6A:
								child = new PtgRefErr(buffer, max, index); break;
							case 0x2B:
							case 0x4B:
							case 0x6B:
								child = new PtgAreaErr(buffer, max, index); break;
							case 0x2C:
							case 0x4C:
							case 0x6C:
								child = new PtgRefN(buffer, max, index); break;
							case 0x2D:
							case 0x4D:
							case 0x6D:
								child = new PtgAreaN(buffer, max, index); break;
							case 0x39:
							case 0x59:
							case 0x79:
								child = new PtgNameX(buffer, max, index); break;
							case 0x3A:
							case 0x5A:
							case 0x7A:
								child = new PtgRef3d(buffer, max, index); break;
							case 0x3B:
							case 0x5B:
							case 0x7B:
								child = new PtgArea3d(buffer, max, index); break;
							case 0x3C:
							case 0x5C:
							case 0x7C:
								child = new PtgRefErr3d(buffer, max, index); break;
							case 0x3D:
							case 0x5D:
							case 0x7D:
								child = new PtgAreaErr3d(buffer, max, index); break;								
							default: 
								child = new PtgUnknown(ptgType, 0); 
								index++;
								break;
							}

							index += child->bytesRead;
							list.push_back(child);
						}

						this->bytesRead = index - offset;
					}

					std::string ToTextString(IRecordParser* engine) {
						std::ostringstream ss;
						for (auto it = this->list.begin(); it != this->list.end(); it++) {
							if (it != this->list.begin()) { ss << ";"; }
							auto ptg = (*it);
							if (PtgName* pn = dynamic_cast<PtgName*>(ptg)) {
								auto r = engine->GetRecordOfType(0x0018, pn->nameindex - 1); //LblRecord
								if (INameable* n = dynamic_cast<INameable*>(r)) {
									ss << "PtgName(" << n->GetName() << ")";
								}
							}
							else if (PtgNameX* pnx = dynamic_cast<PtgNameX*>(ptg)) {
								auto r = engine->GetRecordOfType(0x0023, pnx->nameindex - 1); //ExternNameRecord
								if (INameable* n = dynamic_cast<INameable*>(r)) {
									ss << "PtgNameX(" << n->GetName() << ")";
								}
							}
							else {
								ss << ptg->to_string();
							}							
						}
						return ss.str();
					}
				};
			}
		}
	}
}
