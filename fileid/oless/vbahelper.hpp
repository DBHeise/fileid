#pragma once

#include <vector>
#include <tuple>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "pole.h"
#include "..\common.hpp"
#include "OleCommon.hpp"
#include "olessoffice.hpp"

#include <math.h>
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

namespace OleStructuredStorage {
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
			VbaExtensionInfo() {
				this->Extension = ".vba";
				this->VersionName = "Visual Basic for Applications";
			};
			virtual std::string ToJson() {
				std::ostringstream str;
				str << "{";
				str << "\"extension\" : \"" << this->Extension << "\"";
				str << ", \"name\" : \"" << this->VersionName << "\"";
				str << ", \"ProjectName\" : \"" << this->ProjectName << "\"";
				str << ", \"ProjectVersion\" : " << this->Version;
				str << ", \"VBAVersionMajor\" : " << this->VBAVersionMajor;
				str << ", \"VBAVersionMinor\" : " << this->VBAVersionMinor;

				str << ", \"References\" : [" << common::helper::vector_join(this->References, ",", true) << "]";

				str << ", \"Modules\" : [";
				for (std::vector<ProjectModule*>::const_iterator i = this->Modules.begin(); i != this->Modules.end(); i++) {
					if (i != this->Modules.begin()) str << ",";
					str << "{";
					str << "\"Name\":\"" << (*i)->Name << "\"";
					str << ",\"StreamName\":\"" << (*i)->StreamName << "\"";
					str << ",\"Offset\":" << (*i)->Offset;
					str << ",\"isPrivate\":" << (*i)->isPrivate;
					str << ",\"isReadOnly\":" << (*i)->isReadOnly;
					std::string code = (*i)->Code;
					str << ",\"Code\":\"" << common::helper::JsonEscape((*i)->Code) << "\"";
					str << "}";
				}
				str << "]";

				str << "}";
				return str.str();
			}
			virtual std::string ToXml() {
				std::ostringstream str;
				str << "<item>";
				str << "<extension>" << this->Extension << "</extension>";
				str << "<name>" << this->VersionName << "</name>";
				str << "<ProjectName>" << this->ProjectName << "</ProjectName>";
				str << "<ProjectVersion>" << this->Version << "</ProjectVersion>";
				str << "<VBAVersionMajor>" << this->VBAVersionMajor << "</VBAVersionMajor>";
				str << "<VBAVersionMinor>" << this->VBAVersionMinor << "</VBAVersionMinor>";

				str << "<References>";
				for (std::vector<std::string>::const_iterator i = this->References.begin(); i != this->References.end(); i++) {
					str << "<Reference>" << *i << "</Reference>";
				}
				str << "</References>";


				str << "<Modules>";
				for (std::vector<ProjectModule*>::const_iterator i = this->Modules.begin(); i != this->Modules.end(); i++) {
					if (i != this->Modules.begin()) str << ",";
					str << "<Module>";
					str << "<Name>" << (*i)->Name << "</Name>";
					str << "<StreamName>" << (*i)->StreamName << "</StreamName>";
					str << "<Offset>" << (*i)->Offset << "</Offset>";
					str << "<isPrivate>" << (*i)->isPrivate << "</isPrivate>";
					str << "<isReadOnly>" << (*i)->isReadOnly << "</isReadOnly>";
					str << "<Code><![CDATA[" << (*i)->Code << "]]></Code>";
					str << "</Module>";
				}
				str << "</Modules>";
				str << "</item>";
				return str.str();
			}
			virtual std::string ToText() {
				std::ostringstream str;
				str << this->Extension << "\t" << this->Version << "\t" << this->VersionName;
				str << "\t" << this->ProjectName;
				str << "\t" << this->Version;
				str << "\t" << this->VBAVersionMajor;
				str << "\t" << this->VBAVersionMinor;
				return str.str();
			}
			virtual std::string ToCsv() {
				std::ostringstream str;
				str << this->Extension << "," << this->Version << "," << this->VersionName;
				str << "," << this->ProjectName;
				str << "," << this->Version;
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

			static std::tuple<unsigned int, unsigned char*> FetchStream(POLE::Storage *storage, std::string streamFullName, unsigned int offset) {
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

			static std::tuple<unsigned int, unsigned char*> FetchAndDecompress(POLE::Storage *storage, std::string streamFullName, unsigned int offset) {
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

			static std::pair<unsigned int, std::string> ReadString(unsigned char* buffer, unsigned int startIndex) {
				unsigned int len = common::helper::GetItem4Byte(buffer, startIndex);
				std::string  str = common::helper::GetItemString(buffer, startIndex + 4, len);
				return std::make_pair(startIndex + len + 4, str);
			}


			static std::pair<unsigned int, std::wstring> ReadStringW(unsigned char* buffer, unsigned int startIndex) {
				unsigned int len = common::helper::GetItem4Byte(buffer, startIndex);
				std::wstring  str = common::helper::GetItemStringW(buffer, startIndex + 4, len);
				return std::make_pair(startIndex + len + 4, str);
			}

			static std::string GetCode(POLE::Storage* storage, std::string fullname, unsigned int offset) {
				unsigned int len;
				unsigned char* buffer;
				std::tie(len, buffer) = FetchAndDecompress(storage, fullname, offset);
				return common::helper::GetItemString(buffer, 0, len);
			}
		public:
			vbahelper() {}
			~vbahelper() {}

			VbaExtensionInfo* Analyze(std::string fullname, POLE::Storage* vbaStorage) {

				VbaExtensionInfo* ans = new VbaExtensionInfo();
				unsigned int len;
				unsigned char* buffer;

				//Read VBA Version
				POLE::Stream* stream = new POLE::Stream(vbaStorage, fullname + "/VBA/_VBA_PROJECT");
				VBAProjectStreamHeader* header = OleStructuredStorage::OleHelper::GetStructFromStream<VBAProjectStreamHeader>(stream);
				ans->Version = header->Version;
				delete stream;


				//Read Project Information
				std::tie(len, buffer) = FetchAndDecompress(vbaStorage, fullname + "/VBA/dir", 0);
				unsigned int index = 40;

				std::string tmpStr;
				std::wstring tmpwStr;
				std::tie(index, tmpStr) = ReadString(buffer, index); //Project Name
				ans->ProjectName = tmpStr;
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //DocString
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //DocStringUnicode
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //ProjectHelpFilePath1
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //ProjectHelpFilePath2
				index += 10; //ProjectHelpContext
				index += 10; //ProjectLibFlags
				ProjectVersion* pVersion = (ProjectVersion*)&buffer[index];
				ans->VBAVersionMajor = pVersion->VersionMajor;
				ans->VBAVersionMinor = pVersion->VersionMinor;
				index += 12; //ProjectVersion
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //ProjectConstants
				std::tie(index, tmpStr) = ReadString(buffer, index + 2); //ProjectConstants Unicode

																							//Read References
				while (common::helper::GetItem2Byte(buffer, index) == 0x16) {
					std::tie(index, tmpStr) = ReadString(buffer, index + 2); //Reference Name
					ans->References.push_back(tmpStr);
					std::tie(index, tmpStr) = ReadString(buffer, index + 2); //Reference Unicode Name

					unsigned short recordType = common::helper::GetItem2Byte(buffer, index);
					index += 2;
					switch (recordType) {
					case 0x33://REFRENCECONTROL		
						std::tie(index, tmpStr) = ReadString(buffer, index); //LibTwiddled
						break;
					case 0x2f://REFRENCECONTROL		
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, index); //LibTwiddled
						index += 6;
						std::tie(index, tmpStr) = ReadString(buffer, index + 2); //Reference Name
						std::tie(index, tmpStr) = ReadString(buffer, index + 2); //Reference Unicode Name
						index += 6;
						std::tie(index, tmpStr) = ReadString(buffer, index + 2); //LibExtended
						index += 26;
						break;
					case 0x0d: //REFERENCEREGISTERED
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, index); //Libid
						index += 6;
						break;
					case 0x0e: //REFERENCEPROJECT
						index += 4;
						std::tie(index, tmpStr) = ReadString(buffer, index); //LibidAbsolute
						std::tie(index, tmpStr) = ReadString(buffer, index); //LibidRelative
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
					unsigned short id = common::helper::GetItem2Byte(buffer, index);

					while (id != 0x2B && index < len) {
						id = common::helper::GetItem2Byte(buffer, index);
						index += 2;
						switch (id) {
						case 0x19: //ModuleName
							std::tie(index, tmpStr) = ReadString(buffer, index);
							mod->Name = tmpStr;
							break;
						case 0x47: //ModuleNameUnicode
							std::tie(index, tmpStr) = ReadString(buffer, index);
							break;
						case 0x1A: //ModuleStreamName
							std::tie(index, tmpStr) = ReadString(buffer, index);
							mod->StreamName = tmpStr;
							index += 2;
							std::tie(index, tmpStr) = ReadString(buffer, index);
							break;
						case 0x1C: //ModuleDocString
							std::tie(index, tmpStr) = ReadString(buffer, index);
							index += 2;
							std::tie(index, tmpStr) = ReadString(buffer, index);
							break;
						case 0x31: //ModuleOffset
							index += 4;
							mod->Offset = common::helper::GetItem4Byte(buffer, index);
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
						std::string newStreamName = fullname + "/VBA/" + (std::string)(mod->StreamName);
						mod->Code = GetCode(vbaStorage, newStreamName, (unsigned int)(mod->Offset));
					}
					ans->Modules.push_back(mod);
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

				unsigned char* decompressedBuffer = new unsigned char[compressedBufferLength * 1024];

				if (compressedBuffer[compressedCurrent] != 0x01) {
					return std::make_tuple<unsigned int, unsigned char*>(0, NULL);
				}
				compressedCurrent++;

				while (compressedCurrent < compressedRecordEnd) {
					compressedChunkStart = compressedCurrent;

					//2.4.1.3.2		
					unsigned short headerblock = common::helper::GetItem2Byte(compressedBuffer, compressedCurrent);
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

											unsigned short token = common::helper::GetItem2Byte(compressedBuffer, compressedCurrent);

											unsigned short copyTokenLength = (token & lengthMask) + 3;
											unsigned short copyTokenOffset = ((token & offsetMask) >> (16 - bitCount)) + 1;

											unsigned int copySource = decompressedCurrent - copyTokenOffset;

											for (unsigned int n = copySource; n < (copySource + copyTokenLength); n++) {
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
