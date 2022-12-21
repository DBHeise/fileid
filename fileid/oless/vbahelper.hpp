#pragma once

#include <vector>
#include <tuple>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <locale>
#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"

#include <math.h>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

namespace oless {
	namespace VBA {

		struct MODULEOFFSET {
			unsigned short Id;
			unsigned int Size;
			unsigned int TextOffset;
		};
		struct VBAProjectStreamHeader {
			unsigned short Reserved1;
			unsigned short Version;
			unsigned short Reserved2;
			unsigned short Reserved3;
		};
		struct ProjectSysKind {
			unsigned short Id;
			unsigned int Size;
			unsigned int SysKind;
		};
		struct ProjectLCID {
			unsigned short Id;
			unsigned int Size;
			unsigned int Lcid;
		};
		struct ProjectLCIDInvoke {
			unsigned short Id;
			unsigned int Size;
			unsigned int LcidInvoke;
		};
		struct ProjectCodePage {
			unsigned short Id;
			unsigned int Size;
			unsigned short CodePage;
		};
		struct ProjectName {
			unsigned short Id;
			unsigned int SizeOfProjectName;
			std::string Name;
		};
		struct ProjectDocString {
			unsigned short Id;
			unsigned int SizeOfDocString;
			std::string DocString;
			unsigned short Reserved;
			unsigned int SizeOfDocStringUnicode;
			std::string DocStringUnicode;
		};
		struct ProjectHelpFilePath {
			unsigned short Id;
			unsigned int SizeOfHelpFile1;
			std::string HelpFile1;
			unsigned short Reserved;
			unsigned int SizeOfHelpFile2;
			std::string HelpFile2;
		};
		struct ProjectHelpContext {
			unsigned short Id;
			unsigned int Size;
			unsigned int HelpContext;
		};
		struct ProjectLibFlags {
			unsigned short Id;
			unsigned int Size;
			unsigned int Flags;
		};
		struct ProjectVersion {
			unsigned short Id;
			unsigned int Size;
			unsigned int VersionMajor;
			unsigned short VersionMinor;
		};
		struct ProjectConstants {
			unsigned short Id;
			unsigned int SizeOfConstants;
			std::string Constants;
			unsigned short Reserved;
			unsigned int SizeOfConstantsUnicode;
			std::string ConstantsUnicode;
		};


		struct ProjectInformation {
			ProjectSysKind SysKindRecord;
			ProjectLCID LcidRecord;
			ProjectLCIDInvoke LcidInvokeRecord;
			ProjectCodePage CodePageRecord;
			ProjectName NameRecord;
			ProjectDocString DocStringRecord;
			ProjectHelpFilePath HelpFilePathRecord;
			ProjectHelpContext HelpContextRecord;
			ProjectLibFlags LibFlagsRecord;
			ProjectVersion VersionRecord;
			ProjectConstants ConstantsRecord;
		};

		struct ProjectModule {
			std::string Name;
			std::string StreamName;
			std::string StreamNamePole;
			std::wstring StreamNameW;
			unsigned int Offset;
			std::string Code;
			bool isPrivate;
			bool isReadOnly;
		};


		class VbaExtensionInfo : public common::ExtensionInfo {
		public:
			std::string ProjectName;
			std::vector<std::string> References;
			std::vector<ProjectModule*> Modules;
			unsigned int VBAVersionMajor;
			unsigned short VBAVersionMinor;
			VbaExtensionInfo() : ExtensionInfo() {
				this->Extension = "vba";
				this->Name = "Visual Basic for Applications";
				this->VBAVersionMajor = 0;
				this->VBAVersionMinor = 0;
			};
			virtual std::string ToJson() const {
				std::ostringstream str;
				str << "{";
				str << this->buildBaseJson();				
				if (this->ProjectName.size() > 0) {
					str << ", \"projectname\":\"" << common::JsonEscape(this->ProjectName) << "\"";
				}
				if (this->VBAVersionMajor > 0) {
					str << ", \"VBAVersionMajor\" : " << this->VBAVersionMajor;
				}
				if (this->VBAVersionMinor > 0) {
					str << ", \"VBAVersionMinor\" : " << this->VBAVersionMinor;
				}
				if (this->References.size() > 0) {
					str << ", \"References\" : [" << common::vector_join(this->References, ",", true) << "]";
				}
				if (this->Modules.size() > 0) {
					str << ", \"Modules\" : [";
					for (std::vector<ProjectModule*>::const_iterator i = this->Modules.begin(); i != this->Modules.end(); i++) {
						if (i != this->Modules.begin()) str << ",";
						str << "{";
						str << "\"Name\":\"" << common::JsonEscape((*i)->Name) << "\"";
						str << ",\"StreamName\":\"" << common::JsonEscape((*i)->StreamName) << "\"";
						str << ",\"Offset\":" << (*i)->Offset;
						str << ",\"isPrivate\":" << (*i)->isPrivate;
						str << ",\"isReadOnly\":" << (*i)->isReadOnly;
						std::string code = (*i)->Code;
						str << ",\"Code\":\"" << common::JsonEscape((*i)->Code) << "\"";
						str << "}";
					}
					str << "]";
				}
				str << "}";
				return str.str();
			}
			virtual std::string ToXml() const {
				std::ostringstream str;
				str << "<item>";
				str << this->buildBaseXml();
				if (this->ProjectName.size() > 0) {
					str << "<projectname>" << common::XmlEscape(this->ProjectName) << "</projectname>";
				}
				if (this->VBAVersionMajor > 0) {
					str << "<VBAVersionMajor>" << this->VBAVersionMajor << "</VBAVersionMajor>";
				}
				if (this->VBAVersionMinor > 0) {
					str << "<VBAVersionMinor>" << this->VBAVersionMinor << "</VBAVersionMinor>";
				}
				if (this->References.size() > 0) {
					str << "<References>";
					for (std::vector<std::string>::const_iterator i = this->References.begin(); i != this->References.end(); i++) {
						str << "<Reference>" << *i << "</Reference>";
					}
					str << "</References>";
				}

				if (this->Modules.size() > 0) {
					str << "<Modules>";
					for (std::vector<ProjectModule*>::const_iterator i = this->Modules.begin(); i != this->Modules.end(); i++) {
						if (i != this->Modules.begin()) str << ",";
						str << "<Module>";
						str << "<Name>" << common::XmlEscape((*i)->Name) << "</Name>";
						str << "<StreamName>" << common::XmlEscape((*i)->StreamName) << "</StreamName>";
						str << "<Offset>" << (*i)->Offset << "</Offset>";
						str << "<isPrivate>" << (*i)->isPrivate << "</isPrivate>";
						str << "<isReadOnly>" << (*i)->isReadOnly << "</isReadOnly>";
						str << "<Code><![CDATA[" << (*i)->Code << "]]></Code>";
						str << "</Module>";
					}
					str << "</Modules>";
				}
				str << "</item>";
				return str.str();
			}
			virtual std::string ToText() {
				std::ostringstream str;
				str << this->Extension;
				str << "\t" << this->Name;
				str << "\t" << this->SubType;
				str << "\t" << this->Version;
				str << "\t" << this->VersionName;
				str << "\t" << this->ProjectName;
				str << "\t" << this->VBAVersionMajor;
				str << "\t" << this->VBAVersionMinor;
				return str.str();
			}
			virtual std::string ToCsv() {
				std::ostringstream str;
				str << this->Extension;
				str << "," << this->Name;
				str << "," << this->SubType;
				str << "," << this->Version;
				str << "," << this->VersionName;
				str << "," << this->ProjectName;
				str << "," << this->VBAVersionMajor;
				str << "," << this->VBAVersionMinor;
				return str.str();
			}

		};




		class vbahelper
		{
		private:
			static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
				std::stringstream ss(s);
				std::string item;
				while (std::getline(ss, item, delim)) {
					elems.push_back(item);
				}
				return elems;
			}

			static std::vector<std::string> split(const std::string &s, char delim) {
				std::vector<std::string> elems;
				split(s, delim, elems);
				return elems;
			}

			static unsigned int Extract_CompressedChunkSize(unsigned int header) {
				return (header & 0x0FFF) + 3;
			}
			static unsigned char Extract_CompressedChunkFlag(unsigned int header) {
				return  (header >> 15) & 0x1; //(header & 0x8000) << 15;
			}

			static std::tuple<unsigned int, unsigned char*> FetchStream(POLE::Storage *storage, std::wstring streamFullName, unsigned int offset) {
				POLE::Stream* stream = new POLE::Stream(storage, streamFullName);
				if (stream) {
					unsigned int len = (unsigned int)(stream->size() - offset);
					unsigned char* buffer = new unsigned char[len];
					stream->seek(offset);
					unsigned int actualLen = (unsigned int)stream->read(buffer, len);
					delete stream;
					return std::make_tuple(actualLen, buffer);
				}
				else {
					return std::make_tuple<unsigned int, unsigned char*>(0, NULL);
				}
			}

			static std::tuple<unsigned int, unsigned char*> FetchAndDecompress(POLE::Storage *storage, std::wstring streamFullName, unsigned int offset) {
				unsigned int compressedLength;
				unsigned char* compressed;
				std::tie(compressedLength, compressed) = FetchStream(storage, streamFullName, offset);
				std::tuple<unsigned int, unsigned char*> ans;
				if (compressed) {
					ans = vbahelper::Decompress(compressedLength, compressed);
				}
				else {
					ans = std::make_tuple<unsigned int, unsigned char*>(0, NULL);
				}
				delete compressed;
				return ans;
			}

			static std::pair<unsigned int, std::string> ReadString(unsigned char* buffer, unsigned int bufferLen, unsigned int startIndex) {

				unsigned int len = common::ReadUInt(buffer, bufferLen, startIndex, true);
				std::string  str = common::ReadString(buffer, bufferLen, startIndex + 4, len);
				return std::make_pair(startIndex + len + 4, str);
			}

		
			static std::tuple<unsigned int, std::string, std::wstring> ReadStringW(unsigned char* buffer, unsigned int bufferLen, unsigned int startIndex) {

				unsigned int len = common::ReadUInt(buffer, bufferLen, startIndex, true);
				if (startIndex + 4 + len > bufferLen)
					throw std::runtime_error("Attempted to read past end of buffer");
				
				std::string str;
				for (unsigned int i = startIndex + 4; i < (startIndex + 4 + len); i+=2) {
					str.append(1, buffer[i]);
				}
				wchar_t* wc = reinterpret_cast<wchar_t*>(&buffer[startIndex + 4]);
				std::wstring ws(wc, static_cast<size_t>(len / sizeof(wchar_t)));

				return std::make_tuple(startIndex + len + 4, str, ws);
			/*	std::string str = ws2s(ws);
				return std::make_pair(startIndex + len + 4, str);*/
			}

			static std::string GetCode(POLE::Storage* storage, std::wstring fullname, unsigned int offset) {
				unsigned int len;
				unsigned char* buffer;
				std::tie(len, buffer) = FetchAndDecompress(storage, fullname, offset);
				return common::ReadString(buffer, len, 0, len);
			}
		public:
			vbahelper() {}
			~vbahelper() {}

			VbaExtensionInfo* Analyze(std::wstring fullname, POLE::Storage* vbaStorage) {

				VbaExtensionInfo* ans = new VbaExtensionInfo();
				unsigned int len;
				unsigned char* buffer;

				//Read VBA Version
				POLE::Stream* stream = new POLE::Stream(vbaStorage, fullname + L"/VBA/_VBA_PROJECT");
				VBAProjectStreamHeader* header = oless::GetStructFromStream<VBAProjectStreamHeader>(stream);
				ans->Version = header->Version;
				delete stream;


				//Read Project Information
				std::tie(len, buffer) = FetchAndDecompress(vbaStorage, fullname + L"/VBA/dir", 0);
				unsigned int index = 40;

				std::string tmpStr;
				std::wstring tmpwStr;
				std::tie(index, tmpStr) = ReadString(buffer, len, index); //Project Name
				ans->ProjectName = tmpStr;
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //DocString
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //DocStringUnicode
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //ProjectHelpFilePath1
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //ProjectHelpFilePath2
				index += 10; //ProjectHelpContext
				index += 10; //ProjectLibFlags
				ProjectVersion* pVersion = (ProjectVersion*)&buffer[index];
				ans->VBAVersionMajor = pVersion->VersionMajor;
				ans->VBAVersionMinor = pVersion->VersionMinor;
				index += 12; //ProjectVersion
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //ProjectConstants
				std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //ProjectConstants Unicode

																							//Read References
				while (common::ReadUShort(buffer, len, index) == 0x16) {
					std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //Reference Name
					ans->References.push_back(tmpStr);
					std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //Reference Unicode Name

					unsigned short recordType = common::ReadUShort(buffer, len, index + 2);
					index += 2;
					switch (recordType) {
					case 0x33://REFRENCECONTROL		
						std::tie(index, tmpStr) = ReadString(buffer, len, index); //LibTwiddled
						break;
					case 0x2f://REFRENCECONTROL		
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, len, index); //LibTwiddled
						index += 6;
						std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //Reference Name
						std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //Reference Unicode Name
						index += 6;
						std::tie(index, tmpStr) = ReadString(buffer, len, index + 2); //LibExtended
						index += 26;
						break;
					case 0x0d: //REFERENCEREGISTERED
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, len, index); //Libid
						index += 6;
						break;
					case 0x0e: //REFERENCEPROJECT
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, len, index); //LibidAbsolute
						std::tie(index, tmpStr) = ReadString(buffer, len, index); //LibidRelative
						index += 6;
						break;
					default:
						break;
					}
				}

				//Read Modules	
				index += 16;
				while (index < len) {

					ProjectModule* mod = new ProjectModule();
					mod->Offset = 0;
					mod->isPrivate = false;
					mod->isReadOnly = false;

					//Read Records
					unsigned short id = common::ReadUShort(buffer, len, index);

					while (id != 0x2B && index < len) {
						id = common::ReadUShort(buffer, len, index);
						index += 2;
						switch (id) {
						case 0x19: //ModuleName
							std::tie(index, tmpStr) = ReadString(buffer, len, index);
							mod->Name = tmpStr;
							break;
						case 0x47: //ModuleNameUnicode
							std::tie(index, tmpStr) = ReadString(buffer, len, index);
							break;
						case 0x1A: //ModuleStreamName
							std::tie(index, tmpStr) = ReadString(buffer, len, index);
							mod->StreamName = tmpStr;
							index += 2;
							std::tie(index, tmpStr, tmpwStr) = ReadStringW(buffer, len, index);
							mod->StreamNamePole = tmpStr;
							mod->StreamNameW = tmpwStr;
							break;
						case 0x1C: //ModuleDocString
							std::tie(index, tmpStr) = ReadString(buffer, len, index);
							index += 2;
							std::tie(index, tmpStr) = ReadString(buffer, len, index);
							break;
						case 0x31: //ModuleOffset
							index += 4;
							mod->Offset = common::ReadUInt(buffer, len, index, true);
							index += 4;
							break;
						case 0x1E: //ModuleHelpContext
							index += 8;
							break;
						case 0x2C: //ModuleCookie
							index += 6;
							break;
						case 0x21: //ModuleType = procedural
						case 0x22: //ModuleType = document, class, or designer
							index += 4;
							break;
						case 0x25: //ModuleReadOnly
							mod->isReadOnly = true;
							index += 4;
							break;
						case 0x28: //ModulePrivate
							mod->isPrivate = true;
							index += 4;
							break;
						}
					}
					index += 4;
					if (!(mod->StreamName.empty())) {
						std::wstring newStreamName = fullname + L"/VBA/" + mod->StreamNameW;
						mod->Code = GetCode(vbaStorage, newStreamName, (unsigned int)(mod->Offset));
						ans->Modules.push_back(mod);
					}
				}
				return ans;
			}

			static std::tuple<unsigned int, unsigned char*> Decompress(const unsigned int compressedBufferLength, const unsigned char* compressedBuffer) {

				unsigned int decompressedChunkStart = 0;
				unsigned int decompressedCurrent = 0;
				unsigned int compressedRecordEnd = compressedBufferLength;
				unsigned int compressedCurrent = 0;
				unsigned int compressedChunkStart = 0;
				unsigned int compressedEnd = 0;

				unsigned int decompressedBufferLength = compressedBufferLength * 1024;

				if (compressedBuffer[compressedCurrent] != 0x01) {
					return std::make_tuple<unsigned int, unsigned char*>(0, NULL);
				}
				unsigned char* decompressedBuffer = new unsigned char[decompressedBufferLength] {0};
				compressedCurrent++;

				while (compressedCurrent < compressedRecordEnd) {
					compressedChunkStart = compressedCurrent;

					//2.4.1.3.2		
					unsigned short headerblock = common::ReadUShort(compressedBuffer, compressedRecordEnd, compressedCurrent);
					unsigned int size = Extract_CompressedChunkSize(headerblock);
					unsigned int sig = (headerblock >> 12) & 0x07;
					if (sig != 3) {
						return std::make_tuple<unsigned int, unsigned char*>(0, NULL);
					}
					unsigned char compressedFlag = Extract_CompressedChunkFlag(headerblock);
					decompressedChunkStart = decompressedCurrent;
					compressedEnd = __min(compressedRecordEnd, compressedChunkStart + size);
					compressedCurrent = compressedChunkStart + 2;
					if (compressedFlag == 1) {
						while (compressedCurrent < compressedEnd) {

							//2.4.1.3.4 - Decompress Token Sequence
							unsigned short byte = compressedBuffer[compressedCurrent];
							compressedCurrent++;
							if (compressedCurrent < compressedEnd) {
								for (unsigned int i = 0; i <= 7; i++) {
									if (compressedCurrent < compressedEnd) {
										//2.4.1.3.5 - Decompress a Token
										unsigned char flag = (byte >> i) & 1;
										if (flag == 0) {
											decompressedBuffer[decompressedCurrent] = compressedBuffer[compressedCurrent];
											decompressedCurrent++;
											compressedCurrent++;
										}
										else {
											//2.4.1.3.19.2 - Unpack CopyToken

											//2.4.1.3.19.1 - CopyToken Help								
											unsigned short bitCount = (unsigned short)__max(ceil(log2(decompressedCurrent - decompressedChunkStart)), (double)4);
											unsigned short lengthMask = 0xFFFF >> bitCount;
											unsigned short offsetMask = ~lengthMask;
											//unsigned short maximumLength = (0xFFFF >> bitCount) + 3;

											unsigned short token = common::ReadUShort(compressedBuffer, compressedBufferLength, compressedCurrent);

											unsigned short copyTokenLength = (token & lengthMask) + 3;
											unsigned short copyTokenOffset = ((token & offsetMask) >> (16 - bitCount)) + 1;

											unsigned int copySource = decompressedCurrent - copyTokenOffset;

											for (unsigned int n = copySource; n < (copySource + copyTokenLength) && n < decompressedBufferLength; n++) {
												decompressedBuffer[decompressedCurrent] = decompressedBuffer[n];
												decompressedCurrent++;
											}
											compressedCurrent = compressedCurrent + 2;
										}
									}
								}
							}

						}
					}
					else {
						//decompress Raw Chunk
						for (unsigned int i = 0; i < compressedEnd; i++) {
							decompressedBuffer[decompressedCurrent] = compressedBuffer[compressedCurrent];
							decompressedCurrent++;
							compressedCurrent++;
						}
					}
				}

				return std::make_tuple(decompressedCurrent, decompressedBuffer);

			}
		};
	}
}
