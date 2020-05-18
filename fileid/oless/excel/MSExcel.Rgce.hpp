#pragma once

#include "MSExcel.common.hpp"

namespace OleStructuredStorage {
	namespace Excel {

		
		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/6df491b9-14e8-4efd-9d92-98db51b7cdbd
		// The RgceArea structure specifies a reference to a rectangular range of cells where relative references are stored as coordinates. 
		class RgceArea {
		public:
			unsigned short rowFirst;
			unsigned short rowLast;
			ColRelU columnFirst;
			ColRelU columnLast;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->columnFirst.col + 1) << this->rowFirst + 1 << ":" << ColNumToName(this->columnLast.col + 1) << this->rowLast + 1;
				return ss.str();
			}
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->rowFirst = common::ReadUShort(buffer, max, offset);
				this->rowLast = common::ReadUShort(buffer, max, offset + 2);
				this->columnFirst.Parse(buffer, offset + 4, max);
				this->columnLast.Parse(buffer, offset + 6, max);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/75afd109-b1ce-4511-b56f-2d63116f6647
		// The RgceAreaRel structure specifies a rectangular range of cells where the relative portions of relative references are specified as offsets from the cell in which the formula (section 2.2.2) is evaluated.
		class RgceAreaRel {
		public:
			unsigned short rowFirst;
			unsigned short rowLast;
			ColRelNegU columnFirst;
			ColRelNegU columnLast;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->rowFirst = common::ReadUShort(buffer, max, offset);
				this->rowLast = common::ReadUShort(buffer, max, offset + 2);
				this->columnFirst.Parse(buffer, offset + 4, max);
				this->columnLast.Parse(buffer, offset + 6, max);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/231fcf3f-9bb2-49dd-b97d-d9389188dc5e
		// The RgceElfLoc structure specifies a location of a cell that contains a label used in a natural language formula to refer to a contiguous range of cells from the same row or column as the cell with the label.
		class RgceElfLoc {
		public:
			unsigned short row;
			ColElfU col;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->row = common::ReadUShort(buffer, max, offset);
				this->col.Parse(buffer, offset + 2, max);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f225058b-61ef-4a94-8f58-1195d8087849
		// ptg=
		// The RgceElfLocExtra structure specifies a single cell reference which specifies a part of a multiple-cell natural language label. The cell is specified as the intersection of the given row and column. 
		class RgceElfLocExtra {
		public:
			unsigned short row;
			ColRelU col;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->row = common::ReadUShort(buffer, max, offset);
				this->col.Parse(buffer, offset + 2, max);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/f2395c33-34a4-4b07-85a9-9bb5f07848d9
		// ptg=
		// The RgceLoc structure specifies a reference to a single cell where relative references are stored as coordinates.
		class RgceLoc {
		public:
			unsigned short row;
			ColRelU col;
			std::string to_string() const {
				std::ostringstream ss;
				ss << ColNumToName(this->col.col + 1) << this->row + 1;
				return ss.str();
			}
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->row = buffer[offset];
				this->col.Parse(buffer, offset, max);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/32ce1ec2-e11b-428c-ba62-d835613968e1
		// ptg=
		// The RgceLoc8 structure  specifies a single cell reference.
		class RgceLoc8 {
		public:
			RgceLoc rgceLoc;
			unsigned int reserved;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->rgceLoc.Parse(buffer, offset, max);
				this->reserved = common::ReadUInt(buffer, max, offset + 4, true);
			}
		};

		// see: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/2db37ba7-32f3-4395-88fe-6646034a5358
		// ptg=
		// The RgceLocRel structure specifies a single cell reference where the relative portions of relative references are specified as offsets from the cell in which the formula (section 2.2.2) is evaluated.
		class RgceLocRel {
		public:
			unsigned short row;
			ColRelNegU col;
			void Parse(unsigned char* buffer, unsigned int offset, unsigned int max) {
				this->row = buffer[offset];
				this->col.Parse(buffer, offset, max);
			}
		};
	}
}
