#pragma once
#include "../pole.h"
#include "../../common.hpp"
#include "FormatId.hpp"
#include "PropertyIdentifier.hpp"
#include "PropertyType.hpp"
#include "Property.hpp"


namespace OleStructuredStorage {
	namespace OlePropertySet {
			
		typedef struct PropertyIdentifierAndOffset {
			PropertyIdentifier PropertyId;
			unsigned int Offset;
		};
		typedef struct PropertySetHeader {
			unsigned int Size;
			unsigned int NumProperties;
		};

		typedef struct PropertySetGroup {
			unsigned char	FMTID[16];
			unsigned int	Offset;
		};

		typedef struct PropertySetStreamHeader
		{
			unsigned short	ByteOrder;
			unsigned short	Version;
			unsigned int	SystemIdentifier;
			unsigned char	CLSID[16];
			unsigned int	NumPropertySets;
		};

		

		std::vector<Property*> ParseStream(POLE::Stream* stream) {
			POLE::uint64 size = stream->size();
			unsigned char* buffer = new unsigned char[size];
			unsigned int currentIndex = 0;
			std::vector<Property*> list;
			if (stream->read(buffer, size) == size) {

				PropertySetStreamHeader* pssh = (PropertySetStreamHeader*)buffer;

				for (unsigned int propertySetIndex = 0; propertySetIndex < pssh->NumPropertySets; propertySetIndex++) {
					currentIndex = sizeof(PropertySetStreamHeader) + (propertySetIndex * sizeof(PropertySetGroup));

					PropertySetGroup* psg = (PropertySetGroup*)(buffer + currentIndex);
					currentIndex = psg->Offset;

					PropertySetHeader* psh = (PropertySetHeader*)(buffer + currentIndex);
					currentIndex += sizeof(PropertySetHeader);

					for (unsigned int pidaoIndex = 0; pidaoIndex < psh->NumProperties; pidaoIndex++) {

						PropertyIdentifierAndOffset* piao = (PropertyIdentifierAndOffset*)(buffer + currentIndex);
						currentIndex += sizeof(PropertyIdentifierAndOffset);

						Property* p = ReadProperty(buffer, size, psg->Offset + piao->Offset, piao->PropertyId);
						if (p != nullptr) {
							p->FMTID = FormatIdFromGuid(psg->FMTID);
							list.push_back(p);
						}
					}
				}
			}
			return list;
		}
	}
}
