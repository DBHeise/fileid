
#pragma once

#include "../../common.hpp"
#include "MSExcel.strings.hpp"


namespace OleStructuredStorage {
	namespace Excel {

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/537671c1-12a2-49f0-96ea-8760fdc411ef
		// ptg=
		// The RevExtern structure specifies a range of sheets on a workbook that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
		class RevExtern {
		public:
			unsigned short book;
			XLUnicodeString path;
			RevItab itabFirst;
			RevItab itabLast;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}

		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/556ac2fe-a736-4f52-97dd-0cf98965252e
		// ptg=
		// The RevItab structure specifies a sheet of a workbook referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
		class RevItab {
		public:
			unsigned char type;
			unsigned short tabid;
			XLUnicodeString sheet;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}

		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/14b8e004-e116-451b-bf84-e26e963aa4a4
		// ptg=
		// The RevLblName structure specifies the name of a defined name that is referenced by a formula in a revision as specified in the Formulas overview (section 2.2.2).
		class RevLblName {
		public:
			unsigned char iBuiltin;
			XLNameUnicodeString st;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}

		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9ef68cc7-45d3-48a1-befd-2882c592e641
		// ptg=
		// The RevName structure specifies a defined name referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
		class RevName {
		public:
			unsigned short book;
			XLUnicodeString path;
			unsigned char fExtern;
			RevNameTabid name;
			RevNamePly externName;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}

		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/fbe58e96-929f-4c7f-9d3b-f5ad8f08dd36
		// ptg=
		// The RevNamePly structure specifies a defined name in an external workbook that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2), and the sheet on which it is defined.
		class RevNamePly {
		public:
			RevSheetName sheet;
			RevLblName name;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/9104e80e-4fce-449f-8658-ae41ba5d3336
		// ptg=
		// The RevNameTabid structure specifies a non-external defined name that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
		class RevNameTabid {
		public:
			unsigned short tabid;
			RevLblName name;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/1713a39f-731d-4508-9e72-14da2b7dd8d3
		// ptg=
		// The RevSheetName structure specifies the sheet or workbook on which a defined name is defined, for a defined name that is referenced by a formula (section 2.2.2) in a revision as specified in the Formulas overview (section 2.2.2).
		class RevSheetName {
		public:
			XLUnicodeString sheet;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				throw std::exception("Not Implemented!");
			}
		};

	}
}