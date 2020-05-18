#pragma once

#include "../../common.hpp"
#include "../OleCommon.hpp"
#include "MSExcel.SerAr.hpp"

namespace OleStructuredStorage {
	namespace Excel {

		std::string GetVersion_Excel(unsigned short version) {
			std::string ans;

			switch (version) {
			case 1280: ans = "BIFF5"; break;
			case 1536: ans = "BIFF8"; break;
			default:  ans = "Unknown"; break;
			}
			return ans;
		}

		std::string GetVisibilityStr(unsigned short visibility) {
			std::string ans;
			switch (visibility) {
			case 0x00: ans = "Visible"; break;
			case 0x01: ans = "Hidden"; break;
			case 0x02: ans = "Very Hidden"; break;
			default: ans = "Unknown/Undocumented visiblitiy"; break;
			}
			return ans;
		}

		std::string GetSheetTypeStr(unsigned short type) {
			std::string ans;
			switch (type) {
			case 0x00: ans = "Worksheet/Dialog"; break;
			case 0x01: ans = "Macro sheet"; break;
			case 0x02: ans = "Chart sheet"; break;
			case 0x06: ans = "VBA Module"; break;
			default: ans = "Unknown/Undocumented type"; break;
			}
			return ans;
		}

		double ReadXNumFromBytes(unsigned char* buffer) {
			union {
				unsigned char data[8];
				double num;
			};
			for (int i = 0; i < 8; i++)
			{
				data[i] = buffer[i];
			}
			return num;
		}

		std::string ColNumToName(const unsigned short col) {
			std::string ans;
			ans.reserve(4);
			unsigned short n = col;
			while (n > 0) {
				ans.insert(0, 1, (char)(65 + (n - 1) % 26));
				n = (n - 1) / 26;
			}
			return ans;
		}


		struct Cell {
			unsigned short rw;
			unsigned short col;
			unsigned short ixfe;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->col + 1) << this->rw + 1;
				return ss.str();				
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/39a0757a-c7bb-4e85-b144-3e7837b059d7
		// The FormulaValue structure specifies the current value of a formula.
		struct FormulaValue {
			unsigned char byte1;
			unsigned char byte2;
			unsigned char byte3;
			unsigned char byte4;
			unsigned char byte5;
			unsigned char byte6;
			unsigned short fExprO;


			std::string Value() const {
				std::string ans;
				if (this->fExprO == 0xFFFF) {
					switch (this->byte1) {
					case 0x00: //String Value
						break;
					case 0x01: //Boolean Value
						break;
					case 0x02: //Error Value
						break;
					case 0x03: //Blank String
						ans = "";
						break;
					}
				}
				else {
					union {
						unsigned char data[8];
						double num;
					};
					data[0] = this->byte1;
					data[1] = this->byte2;
					data[2] = this->byte3;
					data[3] = this->byte4;
					data[4] = this->byte5;
					data[5] = this->byte6;
					data[6] = this->fExprO;
					data[7] = this->fExprO >> 8;

					/*double num;
					*((unsigned char*)(&num) + 0) = this->byte1;
					*((unsigned char*)(&num) + 1) = this->byte2;
					*((unsigned char*)(&num) + 2) = this->byte3;
					*((unsigned char*)(&num) + 3) = this->byte4;
					*((unsigned char*)(&num) + 4) = this->byte5;
					*((unsigned char*)(&num) + 5) = this->byte6;

					*((unsigned short*)(&num) + 6) = this->fExprO;
					ans = std::to_string(num);
					*/
					ans = std::to_string(num);
				}

				return ans;
			}

		};

		struct undoc_cache {
			unsigned short rw;
			unsigned short col : 8;
			unsigned short fIamNotTop : 1;
			unsigned short fNotNull : 1;
			unsigned short fEnt : 1;
			unsigned short itab : 5;

		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8e3c6978-6c9f-4915-a826-07613204b244
		// The Formula record specifies a formula (section 2.2.2) for a cell.
		struct FormulaHeader {
			Cell cell;
			FormulaValue val;
			unsigned short fAlwaysCalc : 1;
			unsigned short fCaclOnLoad : 1; //reserved1
			unsigned short fFill : 1;
			unsigned short fShrFmla : 1;
			unsigned short fNeedBuild : 1;	//reserved2
			unsigned short fClearErrors : 1;
			unsigned short reserved3 : 10;	//unused?
			undoc_cache chn;
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/62a57ab3-11b5-45df-9d92-0a712d94937a
		// The ColElfU structure specifies the zero-based index of a column in a sheet and relative reference information for this column index and a corresponding row index.
		struct ColElfU {
			unsigned short col : 14;
			unsigned char fQuoted : 1;
			unsigned char fRelative : 1;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->col = common::ReadUShort(buffer, max, offset) << 1 >> 1;
				this->fQuoted = common::ExtractBits(buffer[offset + 1], 1, 6);
				this->fRelative = common::ExtractBits(buffer[offset + 1], 1, 7);
			}
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6e5eed10-5b77-43d6-8dd0-37345f8654ad
		// The ColRelU structure specifies the zero-based index of a column in a sheet and relative reference information for this column index and a corresponding row index.
		struct ColRelU {
			unsigned short col : 14;
			unsigned char colRelative : 1;
			unsigned char rowRelative : 1;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->col + 1) << "[" << std::to_string(this->rowRelative) << "," << std::to_string(this->colRelative) << "]";
				return ss.str();
			}
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->col = common::ReadUShort(buffer, max, offset) << 1 >> 1;
				this->colRelative = common::ExtractBits(buffer[offset + 1], 1, 6);
				this->rowRelative = common::ExtractBits(buffer[offset + 1], 1, 7);
			}

		};
		
		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/174e856e-bd82-4ea5-bf75-cf441e7657a1
		// The ColRelNegU structure specifies the zero-based column index of a column in a sheet offset information for this column index and a corresponding row index.
		struct ColRelNegU {
			signed short col : 14;
			unsigned char colRelative : 1;
			unsigned char rowRelative : 1;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->col + 1) << "[" << std::to_string(this->rowRelative) << "," << std::to_string(this->colRelative) << "]";
				return ss.str();
			}
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->col = common::ReadSShort(buffer, max, offset) << 1 >> 1;
				this->colRelative = common::ExtractBits(buffer[offset + 1], 1, 6);
				this->rowRelative = common::ExtractBits(buffer[offset + 1], 1, 7);
			}

		};
		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/809af298-1e4f-499f-9bca-3cd1021f4934
		// The Ref8U structure specifies a range of cells on the sheet.
		struct Ref8U {
			unsigned short rwFirst;
			unsigned short rwLast;
			unsigned short colFirst;
			unsigned short colLast;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->colFirst + 1) << this->rwFirst + 1 << ":" << ColNumToName(this->colLast + 1) << this->rwLast + 1;
				return ss.str();
			}
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->rwFirst = common::ReadUShort(buffer, max, offset);
				this->rwLast = common::ReadUShort(buffer, max, offset + 2);
				this->colFirst = common::ReadUShort(buffer, max, offset + 4);
				this->colLast = common::ReadUShort(buffer, max, offset + 6);
			}
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/3ba6adc8-2581-4758-b322-29718f8ed125
		// The PtgAttrSpaceType structure specifies the number of space or carriage return characters and position of those characters.
		struct PtgAttrSpaceType {
			unsigned char type;
			unsigned char cch;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				if (offset + 1 <= max) {
					this->type = buffer[offset];
					this->cch = buffer[offset + 1];
				}
			}
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/80d504ba-eb5d-4a0f-a5da-3dcc792dd78e
		// The PtgDataType enumeration specifies the data type of a Ptg.
		enum class PtgDataType : unsigned char {
			REFERENCE = 0x1,
			VALUE = 0x2,
			ARRAY = 0x3
		};

		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/91beb411-d175-4c4e-b65f-e3bfbc53064c
		// The BErr structure is a 1 byte unsigned integer that specifies an error. 
		enum class BErr : unsigned char {
			NULL_Err = 00,
			DIVByZero_Err = 0x07,
			VALUE_Err = 0x0F,
			REF_Err = 0x17,
			NAME_Err = 0x1D,
			NUM_Err = 0x24,
			NA_Err = 0x2A,
		};




		// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/edd64b46-0fa0-4ef0-b95b-fe2cd41c7f73
		// The PtgExtraArray structure specifies the values for the corresponding PtgArray as specified in RgbExtra. 
		struct PtgExtraArray {
			unsigned char cols;
			unsigned char rows;
			SerAr a[0];
		};

	}
}