#pragma once
#include "../pole.h"
#include "../../common.hpp"
#include "FormatId.hpp"
#include "PropertyIdentifier.hpp"
#include "PropertyType.hpp"
#include "Property.hpp"


namespace oless {
	namespace propset {
			
		struct PropertyIdentifierAndOffset {
			PropertyIdentifier PropertyId;
			unsigned int Offset;
		};
		struct PropertySetHeader {
			unsigned int Size;
			unsigned int NumProperties;
		};

		struct PropertySetGroup {
			unsigned char	FMTID[16];
			unsigned int	Offset;
		};

		struct PropertySetStreamHeader
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
			unsigned int index = 0;
			std::vector<Property*> children;
			if (stream->read(buffer, size) == size && size > 0) {

				if (index + sizeof(PropertySetStreamHeader) > size) {
					throw std::range_error("Offset would read past end of buffer");
				}
				PropertySetStreamHeader* pssh = (PropertySetStreamHeader*)buffer;
				index += sizeof(PropertySetStreamHeader);


				for (unsigned int propertySetIndex = 0; propertySetIndex < pssh->NumPropertySets; propertySetIndex++) {
					index = sizeof(PropertySetStreamHeader) + (propertySetIndex * sizeof(PropertySetGroup));

					if (index + sizeof(PropertySetGroup) > size) {
						throw std::range_error("Offset would read past end of buffer");
					}
					PropertySetGroup* psg = (PropertySetGroup*)(buffer + index);
					index = psg->Offset;

					if (index + sizeof(PropertySetHeader) > size) {
						throw std::range_error("Offset would read past end of buffer");
					}
					PropertySetHeader* psh = (PropertySetHeader*)(buffer + index);
					index += sizeof(PropertySetHeader);

					for (unsigned int pidaoIndex = 0; pidaoIndex < psh->NumProperties; pidaoIndex++) {

						PropertyIdentifierAndOffset* piao = (PropertyIdentifierAndOffset*)(buffer + index);
						index += sizeof(PropertyIdentifierAndOffset);

						Property* p = ReadProperty(buffer, size, psg->Offset + piao->Offset, piao->PropertyId);
						if (p != nullptr) {
							p->FMTID = FormatIdFromGuid(psg->FMTID);
							children.push_back(p);
						}
					}
				}
			}
			return children;
		}
	}
}
