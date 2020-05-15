#pragma once
#include "../../common.hpp"

namespace OleStructuredStorage {
	namespace OlePropertySet {

		typedef unsigned int PropertyType;

		//taken from https://docs.microsoft.com/en-us/openspecs/windows_protocols/MS-OLEPS/f122b9d7-e5cf-4484-8466-83f6fd94b3cc
		const PropertyType VT_EMPTY = 0x0000; //MUST be zero bytes in length.
		const PropertyType VT_NULL = 0x0001; //MUST be zero bytes in length.
		const PropertyType VT_I2 = 0x0002; //MUST be a 16-bit signed integer, followed by zero padding to 4 bytes.
		const PropertyType VT_I4 = 0x0003; //MUST be a 32-bit signed integer.
		const PropertyType VT_R4 = 0x0004; //MUST be a 4-byte (single-precision) IEEE floating-point number.
		const PropertyType VT_R8 = 0x0005; //MUST be an 8-byte (double-precision) IEEE floating-point number.
		const PropertyType VT_CY = 0x0006; //MUST be a CURRENCY (Packet Version).
		const PropertyType VT_DATE = 0x0007; //MUST be a DATE (Packet Version).
		const PropertyType VT_BSTR = 0x0008; //MUST be a CodePageString.
		const PropertyType VT_ERROR = 0x000A; //MUST be a 32-bit unsigned integer representing an HRESULT, as specified in [MS-DTYP] section 2.2.18.
		const PropertyType VT_BOOL = 0x000B; //MUST be a VARIANT_BOOL as specified in [MS-OAUT] section 2.2.27, followed by zero padding to 4 bytes.
		const PropertyType VT_VARIANT = 0x000C;
		const PropertyType VT_DECIMAL = 0x000E; //MUST be a DECIMAL (Packet Version).
		const PropertyType VT_I1 = 0x0010; //MUST be a 1-byte signed integer, followed by zero padding to 4 bytes.
		const PropertyType VT_UI1 = 0x0011; //MUST be a 1-byte unsigned integer, followed by zero padding to 4 bytes.
		const PropertyType VT_UI2 = 0x0012; //MUST be a 2-byte unsigned integer, followed by zero padding to 4 bytes.
		const PropertyType VT_UI4 = 0x0013; //MUST be a 4-byte unsigned integer.
		const PropertyType VT_I8 = 0x0014; //MUST be an 8-byte signed integer.
		const PropertyType VT_UI8 = 0x0015; //MUST be an 8-byte unsigned integer.
		const PropertyType VT_INT = 0x0016; //MUST be a 4-byte signed integer.
		const PropertyType VT_UINT = 0x0017; //MUST be a 4-byte unsigned integer.
		const PropertyType VT_LPSTR = 0x001E; //MUST be a CodePageString.
		const PropertyType VT_LPWSTR = 0x001F; //MUST be a UnicodeString.
		const PropertyType VT_FILETIME = 0x0040; //MUST be a FILETIME (Packet Version).
		const PropertyType VT_BLOB = 0x0041; //MUST be a BLOB.
		const PropertyType VT_STREAM = 0x0042; //MUST be an IndirectPropertyName. The storage representing the (non-simple) property set MUST have a stream element with this name.
		const PropertyType VT_STORAGE = 0x0043; //MUST be an IndirectPropertyName. The storage representing the (non-simple) property set MUST have a storage element with this name.
		const PropertyType VT_STREAMED_OBJECT = 0x0044; //MUST be an IndirectPropertyName. The storage representing the (non-simple) property set MUST have a stream element with this name.
		const PropertyType VT_STORED_OBJECT = 0x0045; //MUST be an IndirectPropertyName. The storage representing the (non-simple) property set MUST have a storage element with this name.
		const PropertyType VT_BLOB_OBJECT = 0x0046; //MUST be a BLOB.
		const PropertyType VT_CF = 0x0047; //MUST be a ClipboardData.
		const PropertyType VT_CLSID = 0x0048; //MUST be a GUID (Packet Version).
		const PropertyType VT_VERSIONED_STREAM = 0x0049; //MUST be a VersionedStream. The storage representing the (non-simple) property set MUST have a stream element with the name in the StreamName field.
		const PropertyType VT_VECTOR = 0x1000;
		const PropertyType VT_ARRAY = 0x2000;

		std::string PropertyTypeToString(PropertyType pt) {
			switch (pt)
			{
			case VT_EMPTY: { return "VT_EMPTY"; break; }
			case VT_NULL: { return "VT_NULL"; break; }
			case VT_I2: { return "VT_I2"; break; }
			case VT_I4: { return "VT_I4"; break; }
			case VT_R4: { return "VT_R4"; break; }
			case VT_R8: { return "VT_R8"; break; }
			case VT_CY: { return "VT_CY"; break; }
			case VT_DATE: { return "VT_DATE"; break; }
			case VT_BSTR: { return "VT_BSTR"; break; }
			case VT_ERROR: { return "VT_ERROR"; break; }
			case VT_BOOL: { return "VT_BOOL"; break; }
			case VT_DECIMAL: { return "VT_DECIMAL"; break; }
			case VT_I1: { return "VT_I1"; break; }
			case VT_UI1: { return "VT_UI1"; break; }
			case VT_UI2: { return "VT_UI2"; break; }
			case VT_UI4: { return "VT_UI4"; break; }
			case VT_I8: { return "VT_I8"; break; }
			case VT_UI8: { return "VT_UI8"; break; }
			case VT_INT: { return "VT_INT"; break; }
			case VT_UINT: { return "VT_UINT"; break; }
			case VT_LPSTR: { return "VT_LPSTR"; break; }
			case VT_LPWSTR: { return "VT_LPWSTR"; break; }
			case VT_FILETIME: { return "VT_FILETIME"; break; }
			case VT_BLOB: { return "VT_BLOB"; break; }
			case VT_STREAM: { return "VT_STREAM"; break; }
			case VT_STORAGE: { return "VT_STORAGE"; break; }
			case VT_STREAMED_OBJECT: { return "VT_STREAMED_OBJECT"; break; }
			case VT_STORED_OBJECT: { return "VT_STORED_OBJECT"; break; }
			case VT_BLOB_OBJECT: { return "VT_BLOB_OBJECT"; break; }
			case VT_CF: { return "VT_CF"; break; }
			case VT_CLSID: { return "VT_CLSID"; break; }
			case VT_VERSIONED_STREAM: { return "VT_VERSIONED_STREAM"; break; }
			case VT_VECTOR | VT_I2: { return "VT_VECTOR|VT_I2"; break; }
			case VT_VECTOR | VT_I4: { return "VT_VECTOR|VT_I4"; break; }
			case VT_VECTOR | VT_R4: { return "VT_VECTOR|VT_R4"; break; }
			case VT_VECTOR | VT_R8: { return "VT_VECTOR|VT_R8"; break; }
			case VT_VECTOR | VT_CY: { return "VT_VECTOR|VT_CY"; break; }
			case VT_VECTOR | VT_DATE: { return "VT_VECTOR|VT_DATE"; break; }
			case VT_VECTOR | VT_BSTR: { return "VT_VECTOR|VT_BSTR"; break; }
			case VT_VECTOR | VT_ERROR: { return "VT_VECTOR|VT_ERROR"; break; }
			case VT_VECTOR | VT_BOOL: { return "VT_VECTOR|VT_BOOL"; break; }
			case VT_VECTOR | VT_VARIANT: { return "VT_VECTOR|VT_VARIANT"; break; }
			case VT_VECTOR | VT_I1: { return "VT_VECTOR|VT_I1"; break; }
			case VT_VECTOR | VT_UI1: { return "VT_VECTOR|VT_UI1"; break; }
			case VT_VECTOR | VT_UI2: { return "VT_VECTOR|VT_UI2"; break; }
			case VT_VECTOR | VT_UI4: { return "VT_VECTOR|VT_UI4"; break; }
			case VT_VECTOR | VT_I8: { return "VT_VECTOR|VT_I8"; break; }
			case VT_VECTOR | VT_UI8: { return "VT_VECTOR|VT_UI8"; break; }
			case VT_VECTOR | VT_LPSTR: { return "VT_VECTOR|VT_LPSTR"; break; }
			case VT_VECTOR | VT_LPWSTR: { return "VT_VECTOR|VT_LPWSTR"; break; }
			case VT_VECTOR | VT_FILETIME: { return "VT_VECTOR|VT_FILETIME"; break; }
			case VT_VECTOR | VT_CF: { return "VT_VECTOR|VT_CF"; break; }
			case VT_VECTOR | VT_CLSID: { return "VT_VECTOR|VT_CLSID"; break; }
			case VT_ARRAY | VT_I2: { return "VT_ARRAY|VT_I2"; break; }
			case VT_ARRAY | VT_I4: { return "VT_ARRAY|VT_I4"; break; }
			case VT_ARRAY | VT_R4: { return "VT_ARRAY|VT_R4"; break; }
			case VT_ARRAY | VT_R8: { return "VT_ARRAY|VT_R8"; break; }
			case VT_ARRAY | VT_CY: { return "VT_ARRAY|VT_CY"; break; }
			case VT_ARRAY | VT_DATE: { return "VT_ARRAY|VT_DATE"; break; }
			case VT_ARRAY | VT_BSTR: { return "VT_ARRAY|VT_BSTR"; break; }
			case VT_ARRAY | VT_ERROR: { return "VT_ARRAY|VT_ERROR"; break; }
			case VT_ARRAY | VT_BOOL: { return "VT_ARRAY|VT_BOOL"; break; }
			case VT_ARRAY | VT_VARIANT: { return "VT_ARRAY|VT_VARIANT"; break; }
			case VT_ARRAY | VT_DECIMAL: { return "VT_ARRAY|VT_DECIMAL"; break; }
			case VT_ARRAY | VT_I1: { return "VT_ARRAY|VT_I1"; break; }
			case VT_ARRAY | VT_UI1: { return "VT_ARRAY|VT_UI1"; break; }
			case VT_ARRAY | VT_UI2: { return "VT_ARRAY|VT_UI2"; break; }
			case VT_ARRAY | VT_UI4: { return "VT_ARRAY|VT_UI4"; break; }
			case VT_ARRAY | VT_INT: { return "VT_ARRAY|VT_INT"; break; }
			case VT_ARRAY | VT_UINT: { return "VT_ARRAY|VT_UINT"; break; }
			default: { return "Unknown Property Type (" + std::to_string(pt) + ")"; break; }
			}
		}
	}
}