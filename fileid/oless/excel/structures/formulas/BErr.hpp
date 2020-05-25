#pragma once

#include "../../../../common.hpp"
#include "../../../OleCommon.hpp"

namespace oless {
	namespace excel {
		namespace structures {
			namespace formulas {
				
				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/91beb411-d175-4c4e-b65f-e3bfbc53064c
				// The BErr structure is a 1 byte unsigned integer that specifies an error. 
				enum class BErr : unsigned char {
					NULLErr = 00,
					DIVByZero = 0x07,
					VALUE = 0x0F,
					REF = 0x17,
					NAME = 0x1D,
					NUM = 0x24,
					NA = 0x2A,
					GETTING_DATA = 0x2B
				};

				std::string ErrorValueString(BErr e) {
					switch (e) {
					case BErr::NULLErr:		return "#NULL!";
					case BErr::DIVByZero:	return "#DIV/0!";
					case BErr::VALUE:		return "#VALUE!";
					case BErr::REF:			return "#REF!";
					case BErr::NAME:		return "#NAME?";
					case BErr::NUM:			return "#NUM!";
					case BErr::NA:			return "#N/A";
					case BErr::GETTING_DATA:return "#GETTING_DATA";
					}
					return "#UNKNOWN";
				}
			}
		}
	}
}