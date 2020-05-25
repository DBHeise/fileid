#pragma once
#include "../../common.hpp"
#include "PropertyIdentifier.hpp"
#include "PropertyType.hpp"

namespace oless {
	namespace propset {

		struct TypedPropertyValueHeader {
			unsigned short Type;
			unsigned short Padding;
		};


		class Property {
		public:
			PropertyIdentifier  PID;
			FormatId			FMTID;
			PropertyType		Type;

			bool				HasString;
			std::string			String;

			bool				HasInt;
			unsigned long long	Int;

			bool				HasFloat;
			double				Float;

			bool				HasBool;
			bool				Bool;


			Property() :
				PID{ 0 },
				FMTID{ FormatId::FMTID_Unknown },
				Type{ 0 },
				HasString{ false },
				String{ "" },
				HasInt{ false },
				Int{ 0 },
				HasFloat{ false },
				Float{ 0.0 },
				HasBool{ false },
				Bool{ false }
			{}

			std::string ToJson() {
				std::ostringstream str;
				str << "{";
				str << "\"Property\":\"" << PropertyIdentifierToString(this->FMTID, this->PID) << "\"";
				str << ",\"Type\":\"" << PropertyTypeToString(this->Type) << "\"";
				str << ",\"Value\":";
				if (this->HasString) {
					str << "\"" << common::JsonEscape(this->String) << "\"";
				}
				else if (this->HasFloat) {
					str << this->Float;
				}
				else if (this->HasInt) {
					if (this->Type == VT_FILETIME) {
						if (this->PID == PIDSI_EDITTIME) {
							str << "\"" << common::displayDuration(this->Int) << "\""; //duration
						}
						else {
							str << "\"" << common::FileTimeToString(this->Int) << "\""; //date time
						}						
					}
					else {
						str << this->Int;
					}					
				}
				else if (this->HasBool) {
					str << std::boolalpha << this->Bool;
				}
				else {
					str << "\"unknown\"";
				}
				str << "}";
				return str.str();
			}
			std::string ToXML() {
				std::ostringstream str;
				str << "<PropertyItem>";
				str << "<Property>" << PropertyIdentifierToString(this->FMTID, this->PID) << "</Property>";
				str << "<Type>" << PropertyTypeToString(this->Type) << "</Type>";
				str << "<Value>";
				if (this->HasString) {
					str << common::XmlEscape(this->String);
				}
				else if (this->HasFloat) {
					str << this->Float;
				}
				else if (this->HasInt) {

					str << this->Int;
				}
				else if (this->HasBool) {
					str << std::boolalpha << this->Bool;
				}
				else {
					str << "unknown";
				}
				str << "</Value></PropertyItem>";
				return str.str();
			}

		};

		Property* ReadProperty(const unsigned char* buffer, const std::size_t max, const unsigned int offset, const PropertyIdentifier pid) {
			unsigned int index = offset;

			TypedPropertyValueHeader* tpv = (TypedPropertyValueHeader*)(buffer + index);
			index += 4;

			auto ans = new Property();
			ans->PID = pid;
			ans->Type = tpv->Type;

			switch (tpv->Type)
			{
			case VT_BOOL: 
			{
				ans->HasBool = true;
				auto tmp = common::ReadUShort(buffer, max, index);
				ans->Bool = tmp == 0xFFFF;
				break;
			}
			case VT_I2:
				ans->HasInt = true;
				ans->Int = common::ReadSShort(buffer, max, index, true);
				break;
			case VT_I4:
				ans->HasInt = true;
				ans->Int = common::ReadSInt(buffer, max, index, true);
				break;
			case VT_R4:
				ans->HasFloat = true;
				ans->Float = common::ReadFloat(buffer, max, index);
				break;
			case VT_R8:
				ans->HasFloat = true;				
				ans->Float = common::ReadDouble(buffer, max, index);
				break;
			case VT_FILETIME: 
			{
				ans->HasInt = true;
				auto low = common::ReadUInt(buffer, max, index, true);
				auto high = common::ReadUInt(buffer, max, index + 4, true);
				ans->Int = static_cast<unsigned long long>(high) << 32 | low;
				break;
			}
			case VT_BSTR:
			case VT_LPSTR:
			{
				ans->HasString = true;
				//codepage string
				auto size = common::ReadUInt(buffer, max, index, true);
				auto tmpStr = common::ReadString(buffer, max, index + 4, size);
				ans->String = common::erasenulls(tmpStr);
				break;
			}
			case VT_LPWSTR:
			case VT_STREAM:
			case VT_STORAGE:
			case VT_STREAMED_OBJECT:
			case VT_STORED_OBJECT:
			{
				ans->HasString = true;
				//unicode string
				auto size = common::ReadUInt(buffer, max, index, true);
				auto tmpwStr = common::ReadWString(buffer, max, index + 4, (size - 1) * 2);
				ans->String = common::erasenulls(common::convert(tmpwStr));
				break;
			}
			}

			return ans;
		}

	}
}
