#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace oless {
	namespace excel {

		namespace records {

			/*
			CSV taken from table given here: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7d9326d6-691a-4fa1-8dce-42082f38e943
			Powershell to generate case statements
				$data = Import-Csv -Path $CSVFile_FullPath;
				$data | % { $_.RecordType = [int]$_.RecordType };
				$data | sort RecordType |  % { "case " + $_.RecordType + ": ans = `"" + $_.Name + "`"; break;" } | Out-Clipboard
			*/
			std::string GetRecordTypeStr(unsigned short type) {
				std::string ans;
				switch (type) {
				case 6: ans = "Formula"; break;
				case 10: ans = "EOF"; break;
				case 12: ans = "CalcCount"; break;
				case 13: ans = "CalcMode"; break;
				case 14: ans = "CalcPrecision"; break;
				case 15: ans = "CalcRefMode"; break;
				case 16: ans = "CalcDelta"; break;
				case 17: ans = "CalcIter"; break;
				case 18: ans = "Protect"; break;
				case 19: ans = "Password"; break;
				case 20: ans = "Header"; break;
				case 21: ans = "Footer"; break;
				case 23: ans = "ExternSheet"; break;
				case 24: ans = "Lbl"; break;
				case 25: ans = "WinProtect"; break;
				case 26: ans = "VerticalPageBreaks"; break;
				case 27: ans = "HorizontalPageBreaks"; break;
				case 28: ans = "Note"; break;
				case 29: ans = "Selection"; break;
				case 34: ans = "Date1904"; break;
				case 35: ans = "ExternName"; break;
				case 38: ans = "LeftMargin"; break;
				case 39: ans = "RightMargin"; break;
				case 40: ans = "TopMargin"; break;
				case 41: ans = "BottomMargin"; break;
				case 42: ans = "PrintRowCol"; break;
				case 43: ans = "PrintGrid"; break;
				case 47: ans = "FilePass"; break;
				case 49: ans = "Font"; break;
				case 51: ans = "PrintSize"; break;
				case 60: ans = "Continue"; break;
				case 61: ans = "Window1"; break;
				case 64: ans = "Backup"; break;
				case 65: ans = "Pane"; break;
				case 66: ans = "CodePage"; break;
				case 77: ans = "Pls"; break;
				case 80: ans = "DCon"; break;
				case 81: ans = "DConRef"; break;
				case 82: ans = "DConName"; break;
				case 85: ans = "DefColWidth"; break;
				case 89: ans = "XCT"; break;
				case 90: ans = "CRN"; break;
				case 91: ans = "FileSharing"; break;
				case 92: ans = "WriteAccess"; break;
				case 93: ans = "Obj"; break;
				case 94: ans = "Uncalced"; break;
				case 95: ans = "CalcSaveRecalc"; break;
				case 96: ans = "Template"; break;
				case 97: ans = "Intl"; break;
				case 99: ans = "ObjProtect"; break;
				case 125: ans = "ColInfo"; break;
				case 128: ans = "Guts"; break;
				case 129: ans = "WsBool"; break;
				case 130: ans = "GridSet"; break;
				case 131: ans = "HCenter"; break;
				case 132: ans = "VCenter"; break;
				case 133: ans = "BoundSheet8"; break;
				case 134: ans = "WriteProtect"; break;
				case 140: ans = "Country"; break;
				case 141: ans = "HideObj"; break;
				case 144: ans = "Sort"; break;
				case 146: ans = "Palette"; break;
				case 151: ans = "Sync"; break;
				case 152: ans = "LPr"; break;
				case 153: ans = "DxGCol"; break;
				case 154: ans = "FnGroupName"; break;
				case 155: ans = "FilterMode"; break;
				case 156: ans = "BuiltInFnGroupCount"; break;
				case 157: ans = "AutoFilterInfo"; break;
				case 158: ans = "AutoFilter"; break;
				case 160: ans = "Scl"; break;
				case 161: ans = "Setup"; break;
				case 174: ans = "ScenMan"; break;
				case 175: ans = "SCENARIO"; break;
				case 176: ans = "SxView"; break;
				case 177: ans = "Sxvd"; break;
				case 178: ans = "SXVI"; break;
				case 180: ans = "SxIvd"; break;
				case 181: ans = "SXLI"; break;
				case 182: ans = "SXPI"; break;
				case 184: ans = "DocRoute"; break;
				case 185: ans = "RecipName"; break;
				case 189: ans = "MulRk"; break;
				case 190: ans = "MulBlank"; break;
				case 193: ans = "Mms"; break;
				case 197: ans = "SXDI"; break;
				case 198: ans = "SXDB"; break;
				case 199: ans = "SXFDB"; break;
				case 200: ans = "SXDBB"; break;
				case 201: ans = "SXNum"; break;
				case 202: ans = "SxBool"; break;
				case 203: ans = "SxErr"; break;
				case 204: ans = "SXInt"; break;
				case 205: ans = "SXString"; break;
				case 206: ans = "SXDtr"; break;
				case 207: ans = "SxNil"; break;
				case 208: ans = "SXTbl"; break;
				case 209: ans = "SXTBRGIITM"; break;
				case 210: ans = "SxTbpg"; break;
				case 211: ans = "ObProj"; break;
				case 213: ans = "SXStreamID"; break;
				case 215: ans = "DBCell"; break;
				case 216: ans = "SXRng"; break;
				case 217: ans = "SxIsxoper"; break;
				case 218: ans = "BookBool"; break;
				case 220: ans = "DbOrParamQry"; break;
				case 221: ans = "ScenarioProtect"; break;
				case 222: ans = "OleObjectSize"; break;
				case 224: ans = "XF"; break;
				case 225: ans = "InterfaceHdr"; break;
				case 226: ans = "InterfaceEnd"; break;
				case 227: ans = "SXVS"; break;
				case 229: ans = "MergeCells"; break;
				case 233: ans = "BkHim"; break;
				case 235: ans = "MsoDrawingGroup"; break;
				case 236: ans = "MsoDrawing"; break;
				case 237: ans = "MsoDrawingSelection"; break;
				case 239: ans = "PhoneticInfo"; break;
				case 240: ans = "SxRule"; break;
				case 241: ans = "SXEx"; break;
				case 242: ans = "SxFilt"; break;
				case 244: ans = "SxDXF"; break;
				case 245: ans = "SxItm"; break;
				case 246: ans = "SxName"; break;
				case 247: ans = "SxSelect"; break;
				case 248: ans = "SXPair"; break;
				case 249: ans = "SxFmla"; break;
				case 251: ans = "SxFormat"; break;
				case 252: ans = "SST"; break;
				case 253: ans = "LabelSst"; break;
				case 255: ans = "ExtSST"; break;
				case 256: ans = "SXVDEx"; break;
				case 259: ans = "SXFormula"; break;
				case 290: ans = "SXDBEx"; break;
				case 311: ans = "RRDInsDel"; break;
				case 312: ans = "RRDHead"; break;
				case 315: ans = "RRDChgCell"; break;
				case 317: ans = "RRTabId"; break;
				case 318: ans = "RRDRenSheet"; break;
				case 319: ans = "RRSort"; break;
				case 320: ans = "RRDMove"; break;
				case 330: ans = "RRFormat"; break;
				case 331: ans = "RRAutoFmt"; break;
				case 333: ans = "RRInsertSh"; break;
				case 334: ans = "RRDMoveBegin"; break;
				case 335: ans = "RRDMoveEnd"; break;
				case 336: ans = "RRDInsDelBegin"; break;
				case 337: ans = "RRDInsDelEnd"; break;
				case 338: ans = "RRDConflict"; break;
				case 339: ans = "RRDDefName"; break;
				case 340: ans = "RRDRstEtxp"; break;
				case 351: ans = "LRng"; break;
				case 352: ans = "UsesELFs"; break;
				case 353: ans = "DSF"; break;
				case 401: ans = "CUsr"; break;
				case 402: ans = "CbUsr"; break;
				case 403: ans = "UsrInfo"; break;
				case 404: ans = "UsrExcl"; break;
				case 405: ans = "FileLock"; break;
				case 406: ans = "RRDInfo"; break;
				case 407: ans = "BCUsrs"; break;
				case 408: ans = "UsrChk"; break;
				case 425: ans = "UserBView"; break;
					//case 426: ans = "UserSViewBegin_Chart"; break;
				case 426: ans = "UserSViewBegin"; break;
				case 427: ans = "UserSViewEnd"; break;
				case 428: ans = "RRDUserView"; break;
				case 429: ans = "Qsi"; break;
				case 430: ans = "SupBook"; break;
				case 431: ans = "Prot4Rev"; break;
				case 432: ans = "CondFmt"; break;
				case 433: ans = "CF"; break;
				case 434: ans = "DVal"; break;
				case 437: ans = "DconBin"; break;
				case 438: ans = "TxO"; break;
				case 439: ans = "RefreshAll"; break;
				case 440: ans = "HLink"; break;
				case 441: ans = "Lel"; break;
				case 442: ans = "CodeName"; break;
				case 443: ans = "SXFDBType"; break;
				case 444: ans = "Prot4RevPass"; break;
				case 445: ans = "ObNoMacros"; break;
				case 446: ans = "Dv"; break;
				case 448: ans = "Excel9File"; break;
				case 449: ans = "RecalcId"; break;
				case 450: ans = "EntExU2"; break;
				case 512: ans = "Dimensions"; break;
				case 513: ans = "Blank"; break;
				case 515: ans = "Number"; break;
				case 516: ans = "Label"; break;
				case 517: ans = "BoolErr"; break;
				case 519: ans = "String"; break;
				case 520: ans = "Row"; break;
				case 523: ans = "Index"; break;
				case 545: ans = "Array"; break;
				case 549: ans = "DefaultRowHeight"; break;
				case 566: ans = "Table"; break;
				case 574: ans = "Window2"; break;
				case 638: ans = "RK"; break;
				case 659: ans = "Style"; break;
				case 1048: ans = "BigName"; break;
				case 1054: ans = "Format"; break;
				case 1084: ans = "ContinueBigName"; break;
				case 1212: ans = "ShrFmla"; break;
				case 2048: ans = "HLinkTooltip"; break;
				case 2049: ans = "WebPub"; break;
				case 2050: ans = "QsiSXTag"; break;
				case 2051: ans = "DBQueryExt"; break;
				case 2052: ans = "ExtString"; break;
				case 2053: ans = "TxtQry"; break;
				case 2054: ans = "Qsir"; break;
				case 2055: ans = "Qsif"; break;
				case 2056: ans = "RRDTQSIF"; break;
				case 2057: ans = "BOF"; break;
				case 2058: ans = "OleDbConn"; break;
				case 2059: ans = "WOpt"; break;
				case 2060: ans = "SXViewEx"; break;
				case 2061: ans = "SXTH"; break;
				case 2062: ans = "SXPIEx"; break;
				case 2063: ans = "SXVDTEx"; break;
				case 2064: ans = "SXViewEx9"; break;
				case 2066: ans = "ContinueFrt"; break;
				case 2067: ans = "RealTimeData"; break;
				case 2128: ans = "ChartFrtInfo"; break;
				case 2129: ans = "FrtWrapper"; break;
				case 2130: ans = "StartBlock"; break;
				case 2131: ans = "EndBlock"; break;
				case 2132: ans = "StartObject"; break;
				case 2133: ans = "EndObject"; break;
				case 2134: ans = "CatLab"; break;
				case 2135: ans = "YMult"; break;
				case 2136: ans = "SXViewLink"; break;
				case 2137: ans = "PivotChartBits"; break;
				case 2138: ans = "FrtFontList"; break;
				case 2146: ans = "SheetExt"; break;
				case 2147: ans = "BookExt"; break;
				case 2148: ans = "SXAddl"; break;
				case 2149: ans = "CrErr"; break;
				case 2150: ans = "HFPicture"; break;
				case 2151: ans = "FeatHdr"; break;
				case 2152: ans = "Feat"; break;
				case 2154: ans = "DataLabExt"; break;
				case 2155: ans = "DataLabExtContents"; break;
				case 2156: ans = "CellWatch"; break;
				case 2161: ans = "FeatHdr11"; break;
				case 2162: ans = "Feature11"; break;
				case 2164: ans = "DropDownObjIds"; break;
				case 2165: ans = "ContinueFrt11"; break;
				case 2166: ans = "DConn"; break;
				case 2167: ans = "List12"; break;
				case 2168: ans = "Feature12"; break;
				case 2169: ans = "CondFmt12"; break;
				case 2170: ans = "CF12"; break;
				case 2171: ans = "CFEx"; break;
				case 2172: ans = "XFCRC"; break;
				case 2173: ans = "XFExt"; break;
				case 2174: ans = "AutoFilter12"; break;
				case 2175: ans = "ContinueFrt12"; break;
				case 2180: ans = "MDTInfo"; break;
				case 2181: ans = "MDXStr"; break;
				case 2182: ans = "MDXTuple"; break;
				case 2183: ans = "MDXSet"; break;
				case 2184: ans = "MDXProp"; break;
				case 2185: ans = "MDXKPI"; break;
				case 2186: ans = "MDB"; break;
				case 2187: ans = "PLV"; break;
				case 2188: ans = "Compat12"; break;
				case 2189: ans = "DXF"; break;
				case 2190: ans = "TableStyles"; break;
				case 2191: ans = "TableStyle"; break;
				case 2192: ans = "TableStyleElement"; break;
				case 2194: ans = "StyleExt"; break;
				case 2195: ans = "NamePublish"; break;
				case 2196: ans = "NameCmt"; break;
				case 2197: ans = "SortData"; break;
				case 2198: ans = "Theme"; break;
				case 2199: ans = "GUIDTypeLib"; break;
				case 2200: ans = "FnGrp12"; break;
				case 2201: ans = "NameFnGrp12"; break;
				case 2202: ans = "MTRSettings"; break;
				case 2203: ans = "CompressPictures"; break;
				case 2204: ans = "HeaderFooter"; break;
				case 2205: ans = "CrtLayout12"; break;
				case 2206: ans = "CrtMlFrt"; break;
				case 2207: ans = "CrtMlFrtContinue"; break;
				case 2211: ans = "ForceFullCalculation"; break;
				case 2212: ans = "ShapePropsStream"; break;
				case 2213: ans = "TextPropsStream"; break;
				case 2214: ans = "RichTextStream"; break;
				case 2215: ans = "CrtLayout12A"; break;
				case 4097: ans = "Units"; break;
				case 4098: ans = "Chart"; break;
				case 4099: ans = "Series"; break;
				case 4102: ans = "DataFormat"; break;
				case 4103: ans = "LineFormat"; break;
				case 4105: ans = "MarkerFormat"; break;
				case 4106: ans = "AreaFormat"; break;
				case 4107: ans = "PieFormat"; break;
				case 4108: ans = "AttachedLabel"; break;
				case 4109: ans = "SeriesText"; break;
				case 4116: ans = "ChartFormat"; break;
				case 4117: ans = "Legend"; break;
				case 4118: ans = "SeriesList"; break;
				case 4119: ans = "Bar"; break;
				case 4120: ans = "Line"; break;
				case 4121: ans = "Pie"; break;
				case 4122: ans = "Area"; break;
				case 4123: ans = "Scatter"; break;
				case 4124: ans = "CrtLine"; break;
				case 4125: ans = "Axis"; break;
				case 4126: ans = "Tick"; break;
				case 4127: ans = "ValueRange"; break;
				case 4128: ans = "CatSerRange"; break;
				case 4129: ans = "AxisLine"; break;
				case 4130: ans = "CrtLink"; break;
				case 4132: ans = "DefaultText"; break;
				case 4133: ans = "Text"; break;
				case 4134: ans = "FontX"; break;
				case 4135: ans = "ObjectLink"; break;
				case 4146: ans = "Frame"; break;
				case 4147: ans = "Begin"; break;
				case 4148: ans = "End"; break;
				case 4149: ans = "PlotArea"; break;
				case 4154: ans = "Chart3d"; break;
				case 4156: ans = "PicF"; break;
				case 4157: ans = "DropBar"; break;
				case 4158: ans = "Radar"; break;
				case 4159: ans = "Surf"; break;
				case 4160: ans = "RadarArea"; break;
				case 4161: ans = "AxisParent"; break;
				case 4163: ans = "LegendException"; break;
				case 4164: ans = "ShtProps"; break;
				case 4165: ans = "SerToCrt"; break;
				case 4166: ans = "AxesUsed"; break;
				case 4168: ans = "SBaseRef"; break;
				case 4170: ans = "SerParent"; break;
				case 4171: ans = "SerAuxTrend"; break;
				case 4174: ans = "IFmtRecord"; break;
				case 4175: ans = "Pos"; break;
				case 4176: ans = "AlRuns"; break;
				case 4177: ans = "BRAI"; break;
				case 4187: ans = "SerAuxErrBar"; break;
				case 4188: ans = "ClrtClient"; break;
				case 4189: ans = "SerFmt"; break;
				case 4191: ans = "Chart3DBarShape"; break;
				case 4192: ans = "Fbi"; break;
				case 4193: ans = "BopPop"; break;
				case 4194: ans = "AxcExt"; break;
				case 4195: ans = "Dat"; break;
				case 4196: ans = "PlotGrowth"; break;
				case 4197: ans = "SIIndex"; break;
				case 4198: ans = "GelFrame"; break;
				case 4199: ans = "BopPopCustom"; break;
				case 4200: ans = "Fbi2"; break;
				default: ans = "Unknown/Undocumented RecordType"; break;
				}
				return ans;
			}

			class Record : public common::IExportable {
			protected:
				virtual std::string getBaseXml() const {
					std::ostringstream str;
					str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
					str << "<Length>" << this->Length << "</Length>";
					return str.str();
				}
				virtual std::string getBaseJson() const {
					std::ostringstream str;
					str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
					str << "\"Length\":" << this->Length;
					return str.str();

				}
			public:
				unsigned short		 Type;
				std::size_t			 Length;
				std::vector<uint8_t> Data;

				Record(unsigned short type, std::vector<uint8_t> data)
				{
					this->Type = type;
					this->Data = data;
					this->Length = data.size();
				}

				virtual std::string ToXml() const
				{
					std::ostringstream str;
					str << "<Record>";
					str << this->getBaseXml();
					str << "</Record>";
					return str.str();
				}

				virtual std::string ToJson() const
				{
					std::ostringstream str;
					str << "{";
					str << this->getBaseJson();
					str << "}";
					return str.str();
				}
			
				virtual std::string ToCsv() const { return ""; }

				virtual std::string ToText() const { return ""; }

			};

		}


		class IRecordParser {
		public:
			virtual records::Record* GetPrevRecord() = 0;
			virtual records::Record* GetPrevRecordOfType(unsigned short type) = 0;
			virtual records::Record* GetPrevRecordNotOfType(unsigned short type) = 0;
		};

		class IReParseable {
		public:
			virtual void ReParse(IRecordParser* p) = 0;
		};
	}
}