// olessmagic.h
// Generated on: 08/13/2020 15:57:39

#pragma once
#include "../common.hpp"
#include "OleCommon.hpp"
#include "olessdetails.hpp"
namespace oless {
    namespace magic {
        std::vector<oless::OlessInfo*> list;
        void initList() {
            
            list.push_back(new oless::OlessInfo("irm","Microsoft Office Information Rights Managed File","","drm",false,L"/DRMContent",nullptr));
            list.push_back(new oless::OlessInfo("irm","Microsoft Office Encrypted Office File","","encrypted",false,L"/\u0006DataSpaces/DataSpaceMap",nullptr));
            list.push_back(new oless::OlessInfo("doc","Microsoft Office Word File","","",false,L"/WordDocument",document::word::Detailer));
            list.push_back(new oless::OlessInfo("xls","Microsoft Office Excel File","","",true,L"/Workbook",oless::excel::Detailer));
            list.push_back(new oless::OlessInfo("xls","Microsoft Office Excel File","","",true,L"/Book",oless::excel::Detailer));
            list.push_back(new oless::OlessInfo("ppt","Microsoft Office PowerPoint File","","",false,L"/PowerPoint Document",document::powerpoint::Detailer));
            list.push_back(new oless::OlessInfo("ppt","Microsoft Office PowerPoint File","Powerpoint 4.0","",false,L"/PP40",nullptr));
            list.push_back(new oless::OlessInfo("pub","Microsoft Office Publisher File","","",false,L"/Contents",document::publisher::Detailer));
            list.push_back(new oless::OlessInfo("vsd","Microsoft Office Visio File","","",false,L"/VisioDocument",document::visio::Detailer));
            list.push_back(new oless::OlessInfo("msg","Microsoft Office Outlook Mail Message","","",false,L"/__properties_version1.0",nullptr));
            list.push_back(new oless::OlessInfo("obd","Microsoft Office Binder","","",false,L"/Binder",nullptr));
            list.push_back(new oless::OlessInfo("mpp","Microsoft Project File","Project 9","Office 2003",false,L"/Props9",nullptr));
            list.push_back(new oless::OlessInfo("mpp","Microsoft Project File","Project 12","Office 2007",false,L"/Props12",nullptr));
            list.push_back(new oless::OlessInfo("mpp","Microsoft Project File","Project 14","Office 2010",false,L"/Props14",nullptr));
            list.push_back(new oless::OlessInfo("bup","McAfee Quarantied File","","",false,L"/Details",nullptr));
            list.push_back(new oless::OlessInfo("wps","Microsoft Works File","","",false,L"/CONTENTS",nullptr));
            list.push_back(new oless::OlessInfo("wps","Microsoft Works File","","",false,L"/MatOST",nullptr));
            list.push_back(new oless::OlessInfo("sdc","StarOffice Calc File","","",false,L"/StarCalcDocument",nullptr));
            list.push_back(new oless::OlessInfo("sdw","StarOffice Write File","","",false,L"/StarWriterDocument",nullptr));
            list.push_back(new oless::OlessInfo("hwp","Hangul Word Processor File","","",false,L"/HwpSummaryInformation",nullptr));
            list.push_back(new oless::OlessInfo("wp","WordPerfect File","","",false,L"/PerfectOffice_MAIN",document::wp::StreamDetailer));
            list.push_back(new oless::OlessInfo("msi","Microsoft Installer File","","",false,L"/\u4840\u3F3F\u4577\u446C\u3B6A\u45E4\u4824",document::msi::Detailer));
        
		}
	}
}
