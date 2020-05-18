#pragma once

#include <string>
#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {

			struct EncryptionHeaderFlags {
				unsigned int Reserved1 : 1, Reserved2 : 1, fCryptoAPI : 1, fDocProps : 1, fExternal : 1, fAES : 1, Unused : 26;

				std::string ToXML() {
					std::ostringstream str;
					str << "<Flags>";
					str << "<Reserved1>" << this->Reserved1 << "</Reserved1>";
					str << "<Reserved2>" << this->Reserved2 << "</Reserved2>";
					str << "<fCryptoAPI>" << this->fCryptoAPI << "</fCryptoAPI>";
					str << "<fDocProps>" << this->fDocProps << "</fDocProps>";
					str << "<fExternal>" << this->fExternal << "</fExternal>";
					str << "<fAES>" << this->fAES << "</fAES>";
					str << "<Unused>" << this->Unused << "</Unused>";
					str << "</Flags>";
					return str.str();
				}
				std::string ToJSON() {
					std::ostringstream str;
					str << "\"Flags\":{";
					str << "\"Reserved1\":" << this->Reserved1 << ",";
					str << "\"Reserved2\":" << this->Reserved2 << ",";
					str << "\"fCryptoAPI\":" << this->fCryptoAPI << ",";
					str << "\"fDocProps\":" << this->fDocProps << ",";
					str << "\"fExternal\":" << this->fExternal << ",";
					str << "\"fAES\":" << this->fAES << ",";
					str << "\"Unused\":" << this->Unused;
					str << "}";
					return str.str();
				}

			};
			struct EncryptionHeader {
				EncryptionHeaderFlags Flags;
				unsigned int SizeExtra;
				unsigned int AlgID;
				unsigned int AlgIDHash;
				unsigned int KeySize;
				unsigned int ProviderType;
				unsigned int Reserved1;
				unsigned int Reserved2;
				std::string ToXML() {
					std::ostringstream str;
					str << "<EncryptionHeader>";
					str << this->Flags.ToXML();
					str << "<SizeExtra>" << this->SizeExtra << "</SizeExtra>";
					str << "<AlgID>" << this->AlgID << "</AlgID>";
					str << "<AlgIDHash>" << this->AlgIDHash << "</AlgIDHash>";
					str << "<KeySize>" << this->KeySize << "</KeySize>";
					str << "<ProviderType>" << this->ProviderType << "</ProviderType>";
					str << "<Reserved1>" << this->Reserved1 << "</Reserved1>";
					str << "<Reserved2>" << this->Reserved1 << "</Reserved2>";
					str << "</EncryptionHeader>";
					return str.str();
				}
				std::string ToJSON() {
					std::ostringstream str;
					str << "\"EncryptionHeader\":{";
					str << this->Flags.ToJSON() << ",";
					str << "\"SizeExtra\":" << this->SizeExtra << ",";
					str << "\"AlgID\":" << this->AlgID << ",";
					str << "\"AlgIDHash\":" << this->AlgIDHash << ",";
					str << "\"KeySize\":" << this->KeySize << ",";
					str << "\"ProviderType\":" << this->ProviderType << ",";
					str << "\"Reserved1\":" << this->Reserved1 << ",";
					str << "\"Reserved2\":" << this->Reserved1;
					str << "}";
					return str.str();
				}
			};

			struct EncryptionVerifierHeader {
				unsigned int saltSize;
				unsigned char salt[16];
				unsigned char encryptedVerifier[16];
				unsigned int verifierHashSize;
				std::string ToXML() {
					std::ostringstream str;
					str << "<EncryptionVerifierHeader>";
					str << "<SaltSize>" << this->saltSize << "</SaltSize>";
					str << "<Salt>" << common::bin2hex11(this->salt, 16) << "</Salt>";
					str << "<EncryptedVerifier>" << common::bin2hex11(this->encryptedVerifier, 16) << "</EncryptedVerifier>";
					str << "<VerifierHashSize>" << this->verifierHashSize << "</VerifierHashSize>";
					str << "</EncryptionVerifierHeader>";
					return str.str();
				}
				std::string ToJSON() {
					std::ostringstream str;
					str << "\"EncryptionVerifierHeader\":{";
					str << "\"SaltSize\":" << this->saltSize << ",";
					str << "\"Salt\":\"" << common::bin2hex11(this->salt, 16) << "\",";
					str << "\"EncryptedVerifier\":\"" << common::bin2hex11(this->encryptedVerifier, 16) << "\",";
					str << "\"VerifierHashSize\":" << this->verifierHashSize;
					str << "}";
					return str.str();
				}
			};


			std::string GetCryptoAlgorithm(EncryptionHeaderFlags flags, unsigned int algid) {
				if (flags.fCryptoAPI == 0 && flags.fAES == 0 && flags.fExternal == 1 && algid == 0) {
					return "Determined by application";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 0 && flags.fExternal == 0 && algid == 0) {
					return "RC4";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 0 && flags.fExternal == 1 && algid == 0x6801) {
					return "RC4";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 1 && flags.fExternal == 0 && algid == 0) {
					return "128-bit AES";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 1 && flags.fExternal == 0 && algid == 0x660E) {
					return "128-bit AES";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 1 && flags.fExternal == 0 && algid == 0x660F) {
					return "192-bit AES";
				}
				else if (flags.fCryptoAPI == 1 && flags.fAES == 1 && flags.fExternal == 0 && algid == 0x6610) {
					return "256-bit AES";
				}
				return "Unknown algorithm";				
			}

			std::string GetHashName(EncryptionHeaderFlags flags, unsigned int algidhash) {
				if (flags.fExternal == 1 && algidhash == 0) {
					return "Determined by application";
				}
				else if (flags.fExternal == 0 && algidhash == 0) {
					return "SHA-1";
				}
				else if (flags.fExternal == 0 && algidhash == 0x8004) {
					return "SHA-1";
				}	

				return "Unknown hash algorithm";				
			}
			

			// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/cf9ae8d5-4e8c-40a2-95f1-3b31f16b5529
			// The FilePass record specifies the encryption algorithm used to encrypt the workbook and the structure that is used to verify the password provided when attempting to open the workbook.
			class FilePassRecord : public Record {
			private:
				unsigned short wEncryptionType;

				//XOR
				unsigned short key;
				unsigned short verification;

				//RC4
				unsigned short vMajor;
				unsigned short vMinor;
				
				//RC4 Signed
				EncryptionHeaderFlags* flags;
				EncryptionHeader* encHeader;
				std::wstring cspName;
				EncryptionVerifierHeader* verifier;
				std::vector<uint8_t> verifierHash;

				//RC4 Normal
				std::vector<uint8_t> salt;
				std::vector<uint8_t> encVerifier;				

			public:
				FilePassRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) {
					auto buffer = this->Data.data();
					unsigned int max = this->Data.size();
					int offset = 0;
					this->wEncryptionType = common::ReadUShort(buffer, max, offset);
					offset += 2;
					if (this->wEncryptionType == 0x0) {
						//XOR
						this->key = common::ReadUShort(buffer, max, offset);
						this->verification = common::ReadUShort(buffer, max, offset + 2);
						offset += 4;
					}
					else if (this->wEncryptionType == 0x1) {
						//RC4
						this->vMajor = common::ReadUShort(buffer, max, offset);
						this->vMinor = common::ReadUShort(buffer, max, offset + 2);
						offset += 4;

						if ((vMajor == 0x02 || vMajor == 0x03 || vMajor == 0x04) && vMinor == 0x02) {

							//RC4 CryptoAPI Encryption							
							this->flags = reinterpret_cast<EncryptionHeaderFlags*>(buffer + offset);
							offset += 4;
							unsigned int headerSize = common::ReadUInt(buffer, max, offset, true);
							offset += 4;
							this->encHeader = reinterpret_cast<EncryptionHeader*>(buffer + offset);
							offset += 32;
							int byteCount = headerSize - 32;
							std::wstring cspName(reinterpret_cast<wchar_t const*>(buffer + offset), byteCount/2);
							this->cspName = cspName;
							offset += byteCount;

							this->verifier = reinterpret_cast<EncryptionVerifierHeader*>(buffer + offset);
							offset += 40;
							std::vector<unsigned char> hash(reinterpret_cast<unsigned char>(buffer + offset), this->verifier->verifierHashSize);
							this->verifierHash = hash;
							offset += this->verifier->verifierHashSize;
						}
						else if (vMajor == 0x01 && vMinor == 0x01) {
							this->flags = nullptr;
							//RC4 Encryption
							this->salt = common::readBuffer(buffer + offset, 16);
							offset += 16;
							this->encVerifier = common::readBuffer(buffer + offset, 16);
							offset += 16;
							this->verifierHash = common::readBuffer(buffer + offset, 16);
							offset += 16;
						}
						else {
							//Unknown RC4 type?!?!?
						}

					}

				}
				std::string ToXml() const override
				{
					std::ostringstream str;
					str << "<Record>";
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";					
					if (this->wEncryptionType == 0x0) {
						str << "<EncryptionType>XOR</EncryptionType>";
						str << "<XorKey>" << this->key << "</XorKey>";
						str << "<XorVerification>" << this->verification << "</XorVerification>";
					}
					else if (this->wEncryptionType == 0x1) {
						str << "<EncryptionType>RC4</EncryptionType>";
						str << "<RC4Version>";
						str << "<Major>" << this->vMajor << "</Major>";
						str << "<Minor>" << this->vMinor << "</Minor>";
						str << "</RC4Version>";						
						if (this->flags != nullptr) {
							str << this->flags->ToXML();
							str << this->encHeader->ToXML();
							str << "<CSPName>" << common::convert(this->cspName) << "</CSPName>";
							str << this->verifier->ToXML();
							str << "<EncryptedVerifierHash>" << common::bin2hex11(this->verifierHash) << "</EncryptedVerifierHash>";
						} else if (this->salt.size() > 0) {
							str << "<Salt>" << common::bin2hex11(this->salt) << "</Salt>";
							str << "<EncryptedVerifier>" << common::bin2hex11(this->encVerifier) << "</EncryptedVerifier>";
							str << "<EncryptedVerifierHash>" << common::bin2hex11(this->verifierHash) << "</EncryptedVerifierHash>";
						}
					} else {
						str << "<EncryptionType>" << this->wEncryptionType << "</EncryptionType>";
					}

					str << "</Record>";
					return str.str();
				}
				std::string ToJson() const override
				{
					std::ostringstream str;
					str << "{";
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length << ",";
					
					if (this->wEncryptionType == 0x0) {
						str << "\"EncryptionType\":\"XOR\",";
						str << "\"XorKey\": " << this->key << ",";
						str << "\"XorVerification\":" << this->verification;
					}
					else if (this->wEncryptionType == 0x1) {
						str << "\"EncryptionType\":\"RC4\",";
						str << "\"RC4Version\": {";
						str << "\"Major\":" << this->vMajor << ",";
						str << "\"Minor\":" << this->vMinor;
						str << "},";
						if (this->flags != nullptr) {
							str << this->flags->ToJSON() << ",";
							str << this->encHeader->ToJSON() << ",";
							str << "\"CSPName\":\"" << common::convert(this->cspName) << "\",";
							str << this->verifier->ToJSON() << ",";
							str << "\"EncryptedVerifierHash\":\"" << common::bin2hex11(this->verifierHash) << "\"";
						}
						else if (this->salt.size() > 0) {
							str << "\"Salt\":\"" << common::bin2hex11(this->salt) << "\",";
							str << "\"EncryptedVerifier\":\"" << common::bin2hex11(this->encVerifier) << "\",";
							str << "\"EncryptedVerifierHash\":\"" << common::bin2hex11(this->verifierHash) << "\"";
						}
					} else {
						str << "\"EncryptionType\":" << this->wEncryptionType;
					}
					str << "}";
					return str.str();
				}
			};
		}
	}
}
