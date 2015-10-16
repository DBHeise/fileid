#pragma once

#include <string>
#include <vector>
#include "common.hpp"
#include "oless\oless.hpp"
#include "exe\Exec.hpp"


namespace details {

	std::vector<common::ExtensionInfo*> DwgHelper(const std::string file, std::vector<unsigned char> buffer) {
		throw std::exception("Not Implemented");
	}
	std::vector<common::ExtensionInfo*> ExeHelper(const std::string file, std::vector<unsigned char> buffer) {
		return Exec::Detailer(file, buffer);
	}
	std::vector<common::ExtensionInfo*> JpegHelper(const std::string file, std::vector<unsigned char> buffer) {
		throw std::exception("Not Implemented");
	}
	std::vector<common::ExtensionInfo*> Mp4Helper(const std::string file, std::vector<unsigned char> buffer) {
		throw std::exception("Not Implemented");
	}
	std::vector<common::ExtensionInfo*> OleHelper(const std::string file, std::vector<unsigned char> buffer) {
		OleStructuredStorage::Oless* o = new OleStructuredStorage::Oless(file.c_str());
		return o->Guess();		
	}
	std::vector<common::ExtensionInfo*> ZipHelper(const std::string file, std::vector<unsigned char> buffer) {
		throw std::exception("Not Implemented");
	}


}
