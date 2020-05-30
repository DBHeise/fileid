#pragma once
#include "../../common.hpp"
#include "FormatId.hpp"

namespace oless {
	namespace propset {
		typedef unsigned int PropertyIdentifier;

		const PropertyIdentifier DICTIONARY_PROPERTY_IDENTIFIER = 0x00000000;
		const PropertyIdentifier CODEPAGE_PROPERTY_IDENTIFIER = 0x00000001;
		const PropertyIdentifier LOCALE_PROPERTY_IDENTIFIER = 0x80000000;
		const PropertyIdentifier BEHAVIOR_PROPERTY_IDENTIFIER = 0x80000003;

		const PropertyIdentifier PIDSI_TITLE = 0x00000002; //The title of the document.
		const PropertyIdentifier PIDSI_SUBJECT = 0x00000003; //The subject of the document.
		const PropertyIdentifier PIDSI_AUTHOR = 0x00000004; //The author of the document.
		const PropertyIdentifier PIDSI_KEYWORDS = 0x00000005; //Keywords related to the document.
		const PropertyIdentifier PIDSI_COMMENTS = 0x00000006; //Comments related the document.
		const PropertyIdentifier PIDSI_TEMPLATE = 0x00000007; //The application - specific template from which the document was created.
		const PropertyIdentifier PIDSI_LASTAUTHOR = 0x00000008; //The last author of the document.
		const PropertyIdentifier PIDSI_REVNUMBER = 0x00000009; //An application - specific revision number for this version of the document.
		const PropertyIdentifier PIDSI_EDITTIME = 0x0000000A; //A 64 - bit unsigned integer indicating the total amount of time that has been spent editing the document in 100 - nanosecond increments.MUST be encoded as a FILETIME by setting the dwLowDataTime field to the low 32 - bits and the dwHighDateTime field to the high 32 - bits.
		const PropertyIdentifier PIDSI_LASTPRINTED = 0x0000000B; //The most recent time that the document was printed.
		const PropertyIdentifier PIDSI_CREATE_DTM = 0x0000000C; //The time that the document was created.
		const PropertyIdentifier PIDSI_LASTSAVE_DTM = 0x0000000D; //The most recent time that the document was saved.
		const PropertyIdentifier PIDSI_PAGECOUNT = 0x0000000E; //The total number of pages in the document.
		const PropertyIdentifier PIDSI_WORDCOUNT = 0x0000000F; //The total number of words in the document.
		const PropertyIdentifier PIDSI_CHARCOUNT = 0x00000010; //The total number of characters in the document.
		const PropertyIdentifier PIDSI_THUMBNAIL = 0x00000011; //Application - specific clipboard data containing a thumbnail representing the document's contents. MAY be absent.
		const PropertyIdentifier PIDSI_APPNAME = 0x00000012; //The name of the application that was used to create the document.
		const PropertyIdentifier PIDSI_DOC_SECURITY = 0x00000013; //A 32-bit signed integer representing a set of application - suggested access control flags with the following values : 0x00000001 : Password protected, 0x00000002 : Read - only recommended, 0x00000004 : Read - only enforced, 0x00000008 : Locked for annotations

		const PropertyIdentifier PIDDSI_CATEGORY = 0x00000002; // A text string typed by the user that indicates what category the file belongs to (memo, proposal, and so on). It is useful for finding files of same type.
		const PropertyIdentifier PIDDSI_PRESFORMAT = 0x00000003; // Target format for presentation (35mm, printer, video, and so on).
		const PropertyIdentifier PIDDSI_BYTECOUNT = 0x00000004; // Number of bytes.
		const PropertyIdentifier PIDDSI_LINECOUNT = 0x00000005; // Number of lines.
		const PropertyIdentifier PIDDSI_PARCOUNT = 0x00000006; // Number of paragraphs.
		const PropertyIdentifier PIDDSI_SLIDECOUNT = 0x00000007; // Number of slides.
		const PropertyIdentifier PIDDSI_NOTECOUNT = 0x00000008; // Number of pages that contain notes.
		const PropertyIdentifier PIDDSI_HIDDENCOUNT = 0x00000009; // Number of slides that are hidden.
		const PropertyIdentifier PIDDSI_MMCLIPCOUNT = 0x0000000A; // Number of slides that are hidden.
		const PropertyIdentifier PIDDSI_SCALE = 0x0000000B; // Set to True (-1) when scaling of the thumbnail is desired. If not set, cropping is desired.
		const PropertyIdentifier PIDDSI_HEADINGPAIR = 0x0000000C; // Internally used property indicating the grouping of different document parts and the number of items in each group. The titles of the document parts are stored in the TitlesofParts property. The HeadingPairs property is stored as a vector of variants, in repeating pairs of VT_LPSTR (or VT_LPWSTR) and VT_I4 values. The VT_LPSTR value represents a heading name, and the VT_I4 value indicates the count of document parts under that heading.
		const PropertyIdentifier PIDDSI_DOCPARTS = 0x0000000D; // Names of document parts.
		const PropertyIdentifier PIDDSI_MANAGER = 0x0000000E; // Manager of the project.
		const PropertyIdentifier PIDDSI_COMPANY = 0x0000000F; // Company name.
		const PropertyIdentifier PIDDSI_LINKSDIRTY = 0x00000010; // Boolean value to indicate whether the custom links are hampered by excessive noise, for all applications.




		std::string PropertyIdentifierToString(FormatId fid, PropertyIdentifier pi) {
			std::string ans = "Unknown Property Identifier (" + std::to_string(pi) + ")";
			switch (fid) {
			case FormatId::FMTID_DocSummaryInformation:
			{
				switch (pi) {
				case DICTIONARY_PROPERTY_IDENTIFIER: { return "Dictionary"; break; }
				case CODEPAGE_PROPERTY_IDENTIFIER: { return "CodePage"; break; }
				case LOCALE_PROPERTY_IDENTIFIER: { return "Locale"; break; }
				case BEHAVIOR_PROPERTY_IDENTIFIER: { return "Behavior"; break; }
				case PIDDSI_CATEGORY: { return "Category"; break; }
				case PIDDSI_PRESFORMAT: { return "PresentationTarget"; break; }
				case PIDDSI_BYTECOUNT: { return "Bytes"; break; }
				case PIDDSI_LINECOUNT: { return "Lines"; break; }
				case PIDDSI_PARCOUNT: { return "Paragraphs"; break; }
				case PIDDSI_SLIDECOUNT: { return "Slides"; break; }
				case PIDDSI_NOTECOUNT: { return "Notes"; break; }
				case PIDDSI_HIDDENCOUNT: { return "HiddenSlides"; break; }
				case PIDDSI_MMCLIPCOUNT: { return "MMClips"; break; }
				case PIDDSI_SCALE: { return "ScaleCrop"; break; }
				case PIDDSI_HEADINGPAIR: { return "HeadingPairs"; break; }
				case PIDDSI_DOCPARTS: { return "TitlesofParts"; break; }
				case PIDDSI_MANAGER: { return "Manager"; break; }
				case PIDDSI_COMPANY: { return "Company"; break; }
				case PIDDSI_LINKSDIRTY: { return "LinksUpToDate"; break; }
				}
				break;
			}
			case FormatId::FMTID_SummaryInformation:
			{
				switch (pi) {
				case DICTIONARY_PROPERTY_IDENTIFIER: { return "Dictionary"; break; }
				case CODEPAGE_PROPERTY_IDENTIFIER: { return "CodePage"; break; }
				case PIDSI_TITLE: { return "Title"; break; }
				case PIDSI_SUBJECT: { return "Subject"; break; }
				case PIDSI_AUTHOR: { return "Author"; break; }
				case PIDSI_KEYWORDS: { return "Keywords"; break; }
				case PIDSI_COMMENTS: { return "Comments"; break; }
				case PIDSI_TEMPLATE: { return "Template"; break; }
				case PIDSI_LASTAUTHOR: { return "Last Author"; break; }
				case PIDSI_REVNUMBER: { return "Revision"; break; }
				case PIDSI_EDITTIME: { return "Edit Time"; break; }
				case PIDSI_LASTPRINTED: { return "Last Printed"; break; }
				case PIDSI_CREATE_DTM: { return "Creation Time"; break; }
				case PIDSI_LASTSAVE_DTM: { return "Last Save Time"; break; }
				case PIDSI_PAGECOUNT: { return "Page Count"; break; }
				case PIDSI_WORDCOUNT: { return "Word Count"; break; }
				case PIDSI_CHARCOUNT: { return "Character Count"; break; }
				case PIDSI_THUMBNAIL: { return "Thumbnail"; break; }
				case PIDSI_APPNAME: { return "Application"; break; }
				case PIDSI_DOC_SECURITY: { return "DocSecurity"; break; }
				}
				break;
			}
			case FormatId::FMTID_UserDefiniedProperties:
				break;
			default:
				break;
			}
			return ans;


		}
	}

}
