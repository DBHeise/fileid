#pragma once
#include "pole.h"
#include "../common.hpp"
#include "OleCommon.hpp"

namespace OleStructuredStorage {
	namespace OlePropertySet {
		common::helper* h = new	common::helper();


		typedef unsigned int PropertyIdentifier;
		typedef unsigned int PropertyType;

		const PropertyIdentifier DICTIONARY_PROPERTY_IDENTIFIER	= 0x00000000;
		const PropertyIdentifier CODEPAGE_PROPERTY_IDENTIFIER		= 0x00000001;
		const PropertyIdentifier PIDSI_TITLE							= 0x00000002; //The title of the document.
		const PropertyIdentifier PIDSI_SUBJECT							= 0x00000003; //The subject of the document.
		const PropertyIdentifier PIDSI_AUTHOR							= 0x00000004; //The author of the document.
		const PropertyIdentifier PIDSI_KEYWORDS						= 0x00000005; //Keywords related to the document.
		const PropertyIdentifier PIDSI_COMMENTS						= 0x00000006; //Comments related the document.
		const PropertyIdentifier PIDSI_TEMPLATE						= 0x00000007; //The application - specific template from which the document was created.
		const PropertyIdentifier PIDSI_LASTAUTHOR						= 0x00000008; //The last author of the document.
		const PropertyIdentifier PIDSI_REVNUMBER						= 0x00000009; //An application - specific revision number for this version of the document.
		const PropertyIdentifier PIDSI_EDITTIME						= 0x0000000A; //A 64 - bit unsigned integer indicating the total amount of time that has been spent editing the document in 100 - nanosecond increments.MUST be encoded as a FILETIME by setting the dwLowDataTime field to the low 32 - bits and the dwHighDateTime field to the high 32 - bits.
		const PropertyIdentifier PIDSI_LASTPRINTED					= 0x0000000B; //The most recent time that the document was printed.
		const PropertyIdentifier PIDSI_CREATE_DTM						= 0x0000000C; //The time that the document was created.
		const PropertyIdentifier PIDSI_LASTSAVE_DTM					= 0x0000000D; //The most recent time that the document was saved.
		const PropertyIdentifier PIDSI_PAGECOUNT						= 0x0000000E; //The total number of pages in the document.
		const PropertyIdentifier PIDSI_WORDCOUNT						= 0x0000000F; //The total number of words in the document.
		const PropertyIdentifier PIDSI_CHARCOUNT						= 0x00000010; //The total number of characters in the document.
		const PropertyIdentifier PIDSI_THUMBNAIL						= 0x00000011; //Application - specific clipboard data containing a thumbnail representing the document's contents. MAY be absent.
		const PropertyIdentifier PIDSI_APPNAME							= 0x00000012; //The name of the application that was used to create the document.
		const PropertyIdentifier PIDSI_DOC_SECURITY					= 0x00000013; //A 32 - bit signed integer representing a set of application - suggested access control flags with the following values : 0x00000001 : Password protected, 0x00000002 : Read - only recommended, 0x00000004 : Read - only enforced, 0x00000008 : Locked for annotations
		const PropertyIdentifier LOCALE_PROPERTY_IDENTIFIER		= 0x80000000;
		const PropertyIdentifier BEHAVIOR_PROPERTY_IDENTIFIER		= 0x80000003;


		const PropertyType VT_EMPTY				= 0x0000; //Type is undefined, and the minimum property set version is 0. 
		const PropertyType VT_NULL					= 0x0001; //Type is null, and the minimum property set version is 0. 
		const PropertyType VT_I2					= 0x0002; //Type is 16-bit signed integer, and the minimum property set version is 0. 
		const PropertyType VT_I4					= 0x0003; //Type is 32-bit signed integer, and the minimum property set version is 0. 
		const PropertyType VT_R4					= 0x0004; //Type is 4-byte (single-precision) IEEE floating-point number, and the minimum property set version is 0. 
		const PropertyType VT_R8					= 0x0005; //Type is 8-byte (double-precision) IEEE floating-point number, and the minimum property set version is 0. 
		const PropertyType VT_CY					= 0x0006; //Type is CURRENCY, and the minimum property set version is 0. 
		const PropertyType VT_DATE					= 0x0007; //Type is DATE, and the minimum property set version is 0. 
		const PropertyType VT_BSTR					= 0x0008; //Type is CodePageString, and the minimum property set version is 0. 
		const PropertyType VT_ERROR				= 0x000A; //Type is HRESULT, and the minimum property set version is 0. 
		const PropertyType VT_BOOL					= 0x000B; //Type is VARIANT_BOOL, and the minimum property set version is 0. 
		const PropertyType VT_DECIMAL				= 0x000E; //Type is DECIMAL, and the minimum property set version is 0. 
		const PropertyType VT_I1					= 0x0010; //Type is 1-byte signed integer, and the minimum property set version is 1. 
		const PropertyType VT_UI1					= 0x0011; //Type is 1-byte unsigned integer, and the minimum property set version is 0. 
		const PropertyType VT_UI2					= 0x0012; //Type is 2-byte unsigned integer, and the minimum property set version is 0. 
		const PropertyType VT_UI4					= 0x0013; //Type is 4-byte unsigned integer, and the minimum property set version is 0. 
		const PropertyType VT_I8					= 0x0014; //Type is 8-byte signed integer, and the minimum property set version is 0. 
		const PropertyType VT_UI8					= 0x0015; //Type is 8-byte unsigned integer, and the minimum property set version is 0. 
		const PropertyType VT_INT					= 0x0016; //Type is 4-byte signed integer, and the minimum property set version is 1. 
		const PropertyType VT_UINT					= 0x0017; //Type is 4-byte unsigned integer, and the minimum property set version is 1. 
		const PropertyType VT_LPSTR				= 0x001E; //Type is CodePageString, and the minimum property set version is 0. 
		const PropertyType VT_LPWSTR				= 0x001F; //Type is UnicodeString, and the minimum property set version is 0. 
		const PropertyType VT_FILETIME			= 0x0040; //Type is FILETIME, and the minimum property set version is 0. 
		const PropertyType VT_BLOB					= 0x0041; //Type is binary large object (BLOB), and the minimum property set version is 0. 
		const PropertyType VT_STREAM				= 0x0042; //Type is Stream, and the minimum property set version is 0. VT_STREAM is not allowed in a simple property set. 
		const PropertyType VT_STORAGE				= 0x0043; //Type is Storage, and the minimum property set version is 0. VT_STORAGE is not allowed in a simple property set. 
		const PropertyType VT_STREAMED_Object	= 0x0044; //Type is Stream representing an Object in an application-specific manner, and the minimum property set version is 0. VT_STREAMED_Object is not allowed in a simple property set. 
		const PropertyType VT_STORED_Object		= 0x0045; //Type is Storage representing an Object in an application-specific manner, and the minimum property set version is 0. VT_STORED_Object is not allowed in a simple property set. 
		const PropertyType VT_BLOB_Object		= 0x0046; //Type is BLOB representing an object in an application-specific manner. The minimum property set version is 0. 
		const PropertyType VT_CF					= 0x0047; //Type is PropertyIdentifier, and the minimum property set version is 0. 
		const PropertyType VT_CLSID				= 0x0048; //Type is CLSID, and the minimum property set version is 0. 
		const PropertyType VT_VERSIONED_STREAM = 0x0049; //Type is Stream with application-specific version GUID (VersionedStream). The minimum property set version is 0. VT_VERSIONED_STREAM is not allowed in a simple property set. 
		const PropertyType VT_VECTOR				= 0x1000;

		typedef struct _Guid {
			unsigned long  Data1;
			unsigned short Data2;
			unsigned short Data3;
			unsigned char  Data4[8];
		} Guid;

		typedef struct _PropertyIdentifierAndOffset {
			PropertyIdentifier PropertyId;
			unsigned int Offset;
		} PropertyIdentifierAndOffset;

		typedef struct _PropertySetHeader {
			unsigned int Size;
			unsigned int NumProperties;

		} PropertySetHeader;

		typedef struct _TypedPropertyValueHeader {
			unsigned short Type;
			unsigned short Padding;

		} TypedPropertyValueHeader;

		typedef struct _PropertySetIdAndOffset {
			Guid FMTID;
			unsigned int Offset;
		}PropertySetIdAndOffset;

		typedef struct _PropertySetStreamHeader
		{
			unsigned short ByteOrder;
			unsigned short Version;
			unsigned int SystemIdentifier;
			Guid	CLSID;
			unsigned int NumPropertySets;
			//
		} PropertySetStreamHeader;

		void ReadProperty(const unsigned char* buffer, const unsigned int offset, const PropertyIdentifier pid) {
			TypedPropertyValueHeader* tpv = (TypedPropertyValueHeader*)(buffer + offset);
			std::string tmpStr;
			std::wstring tmpwStr;
			unsigned int size = 0;

			if (tpv->Type == VT_EMPTY || tpv->Type == VT_NULL) {}
			else if (tpv->Type == VT_I2) {}
			else if (tpv->Type == VT_I4) {}
			else if (tpv->Type ==  VT_R4) {}
			else if (tpv->Type ==  VT_R8) {}
			else if (tpv->Type ==  VT_CY) {}
			else if (tpv->Type ==  VT_DATE) {}
			else if (tpv->Type ==  VT_ERROR) {}
			else if (tpv->Type ==  VT_BOOL) {}
			else if (tpv->Type ==  VT_DECIMAL) {}
			else if (tpv->Type ==  VT_I1) {}
			else if (tpv->Type ==  VT_UI1) {}
			else if (tpv->Type ==  VT_UI2) {}
			else if (tpv->Type ==  VT_UI4) {}
			else if (tpv->Type ==  VT_I8) {}
			else if (tpv->Type ==  VT_UI8) {}
			else if (tpv->Type ==  VT_INT) {}
			else if (tpv->Type ==  VT_UINT) {}
			else if (tpv->Type ==  VT_FILETIME) {}
			else if (tpv->Type ==  VT_BLOB) {}
			else if (tpv->Type ==  VT_STREAM) {}
			else if (tpv->Type ==  VT_STORAGE) {}
			else if (tpv->Type == VT_STREAMED_Object) {}
			else if (tpv->Type == VT_STORED_Object) {}
			else if (tpv->Type == VT_BLOB_Object) {}
			else if (tpv->Type == VT_CF) {}
			else if (tpv->Type == VT_CLSID) {}
			else if (tpv->Type == VT_VERSIONED_STREAM) {}
			else if (tpv->Type == VT_BSTR || tpv->Type == VT_LPSTR) {
				//codepage string
				size = h->GetItem4Byte(buffer, offset);
				tmpStr = h->GetItemString(buffer, offset + 4, size);
			}
			else if (tpv->Type == VT_LPWSTR) {
				//unicode string
				size = h->GetItem4Byte(buffer, offset);
				tmpwStr = h->GetItemStringW(buffer, offset + 4, size);
			}

			
		}


		void ParseStream(POLE::Stream* stream) {
			POLE::uint64 size = stream->size();			
			unsigned char* buffer = new unsigned char[size];
			unsigned int currentIndex = 0;
			if (stream->read(buffer, size) == size) {

				PropertySetStreamHeader* pssh = (PropertySetStreamHeader*)buffer;				

				for (unsigned int propertySetIndex = 0; propertySetIndex < pssh->NumPropertySets; propertySetIndex++) {
					currentIndex = sizeof(PropertySetStreamHeader) + (propertySetIndex * sizeof(PropertySetIdAndOffset));
					PropertySetIdAndOffset* iao = (PropertySetIdAndOffset*)(buffer + currentIndex);
					currentIndex = iao->Offset;
					PropertySetHeader* psh = (PropertySetHeader*)(buffer + currentIndex);
					currentIndex += sizeof(PropertySetHeader);
					for (unsigned int pidaoIndex = 0; pidaoIndex < psh->NumProperties; pidaoIndex++) {

						PropertyIdentifierAndOffset* piao = (PropertyIdentifierAndOffset*)(buffer + currentIndex);
						currentIndex += sizeof(PropertyIdentifierAndOffset);
						ReadProperty(buffer, iao->Offset + piao->Offset, piao->PropertyId);
					}
				}
			}
		}
	}
}
