#pragma once

#include "../../common.hpp"
#include "../OleCommon.hpp"
#include "MSExcel.common.hpp"


namespace OleStructuredStorage {
	namespace Excel {
		namespace Formulas {

			/*
			CSV taken from table given here: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/00b5dd7d-51ca-4938-b7b7-483fe0e5933b
			Powershell to generate case statements
				$data = Import-Csv -Path $CSVFile_FullPath;
				$data | sort Value |  % { "case " + $_.Value + ": ans = `"" + $_.Meaning + "`"; break;" } | Out-Clipboard
			*/
			std::string GetFunctionName_FTab(unsigned short ftab) {
				std::string ans;
				switch (ftab) {
				case 0x0000: ans = "COUNT"; break;
				case 0x0001: ans = "IF"; break;
				case 0x0002: ans = "ISNA"; break;
				case 0x0003: ans = "ISERROR"; break;
				case 0x0004: ans = "SUM"; break;
				case 0x0005: ans = "AVERAGE"; break;
				case 0x0006: ans = "MIN"; break;
				case 0x0007: ans = "MAX"; break;
				case 0x0008: ans = "ROW"; break;
				case 0x0009: ans = "COLUMN"; break;
				case 0x000A: ans = "NA"; break;
				case 0x000B: ans = "NPV"; break;
				case 0x000C: ans = "STDEV"; break;
				case 0x000D: ans = "DOLLAR"; break;
				case 0x000E: ans = "FIXED"; break;
				case 0x000F: ans = "SIN"; break;
				case 0x0010: ans = "COS"; break;
				case 0x0011: ans = "TAN"; break;
				case 0x0012: ans = "ATAN"; break;
				case 0x0013: ans = "PI"; break;
				case 0x0014: ans = "SQRT"; break;
				case 0x0015: ans = "EXP"; break;
				case 0x0016: ans = "LN"; break;
				case 0x0017: ans = "LOG10"; break;
				case 0x0018: ans = "ABS"; break;
				case 0x0019: ans = "INT"; break;
				case 0x001A: ans = "SIGN"; break;
				case 0x001B: ans = "ROUND"; break;
				case 0x001C: ans = "LOOKUP"; break;
				case 0x001D: ans = "INDEX"; break;
				case 0x001E: ans = "REPT"; break;
				case 0x001F: ans = "MID"; break;
				case 0x0020: ans = "LEN"; break;
				case 0x0021: ans = "VALUE"; break;
				case 0x0022: ans = "TRUE"; break;
				case 0x0023: ans = "FALSE"; break;
				case 0x0024: ans = "AND"; break;
				case 0x0025: ans = "OR"; break;
				case 0x0026: ans = "NOT"; break;
				case 0x0027: ans = "MOD"; break;
				case 0x0028: ans = "DCOUNT"; break;
				case 0x0029: ans = "DSUM"; break;
				case 0x002A: ans = "DAVERAGE"; break;
				case 0x002B: ans = "DMIN"; break;
				case 0x002C: ans = "DMAX"; break;
				case 0x002D: ans = "DSTDEV"; break;
				case 0x002E: ans = "VAR"; break;
				case 0x002F: ans = "DVAR"; break;
				case 0x0030: ans = "TEXT"; break;
				case 0x0031: ans = "LINEST"; break;
				case 0x0032: ans = "TREND"; break;
				case 0x0033: ans = "LOGEST"; break;
				case 0x0034: ans = "GROWTH"; break;
				case 0x0035: ans = "GOTO"; break;
				case 0x0036: ans = "HALT"; break;
				case 0x0037: ans = "RETURN"; break;
				case 0x0038: ans = "PV"; break;
				case 0x0039: ans = "FV"; break;
				case 0x003A: ans = "NPER"; break;
				case 0x003B: ans = "PMT"; break;
				case 0x003C: ans = "RATE"; break;
				case 0x003D: ans = "MIRR"; break;
				case 0x003E: ans = "IRR"; break;
				case 0x003F: ans = "RAND"; break;
				case 0x0040: ans = "MATCH"; break;
				case 0x0041: ans = "DATE"; break;
				case 0x0042: ans = "TIME"; break;
				case 0x0043: ans = "DAY"; break;
				case 0x0044: ans = "MONTH"; break;
				case 0x0045: ans = "YEAR"; break;
				case 0x0046: ans = "WEEKDAY"; break;
				case 0x0047: ans = "HOUR"; break;
				case 0x0048: ans = "MINUTE"; break;
				case 0x0049: ans = "SECOND"; break;
				case 0x004A: ans = "NOW"; break;
				case 0x004B: ans = "AREAS"; break;
				case 0x004C: ans = "ROWS"; break;
				case 0x004D: ans = "COLUMNS"; break;
				case 0x004E: ans = "OFFSET"; break;
				case 0x004F: ans = "ABSREF"; break;
				case 0x0050: ans = "RELREF"; break;
				case 0x0051: ans = "ARGUMENT"; break;
				case 0x0052: ans = "SEARCH"; break;
				case 0x0053: ans = "TRANSPOSE"; break;
				case 0x0054: ans = "ERROR"; break;
				case 0x0055: ans = "STEP"; break;
				case 0x0056: ans = "TYPE"; break;
				case 0x0057: ans = "ECHO"; break;
				case 0x0058: ans = "SET.NAME"; break;
				case 0x0059: ans = "CALLER"; break;
				case 0x005A: ans = "DEREF"; break;
				case 0x005B: ans = "WINDOWS"; break;
				case 0x005C: ans = "SERIES"; break;
				case 0x005D: ans = "DOCUMENTS"; break;
				case 0x005E: ans = "ACTIVE.CELL"; break;
				case 0x005F: ans = "SELECTION"; break;
				case 0x0060: ans = "RESULT"; break;
				case 0x0061: ans = "ATAN2"; break;
				case 0x0062: ans = "ASIN"; break;
				case 0x0063: ans = "ACOS"; break;
				case 0x0064: ans = "CHOOSE"; break;
				case 0x0065: ans = "HLOOKUP"; break;
				case 0x0066: ans = "VLOOKUP"; break;
				case 0x0067: ans = "LINKS"; break;
				case 0x0068: ans = "INPUT"; break;
				case 0x0069: ans = "ISREF"; break;
				case 0x006A: ans = "GET.FORMULA"; break;
				case 0x006B: ans = "GET.NAME"; break;
				case 0x006C: ans = "SET.VALUE"; break;
				case 0x006D: ans = "LOG"; break;
				case 0x006E: ans = "EXEC"; break;
				case 0x006F: ans = "CHAR"; break;
				case 0x0070: ans = "LOWER"; break;
				case 0x0071: ans = "UPPER"; break;
				case 0x0072: ans = "PROPER"; break;
				case 0x0073: ans = "LEFT"; break;
				case 0x0074: ans = "RIGHT"; break;
				case 0x0075: ans = "EXACT"; break;
				case 0x0076: ans = "TRIM"; break;
				case 0x0077: ans = "REPLACE"; break;
				case 0x0078: ans = "SUBSTITUTE"; break;
				case 0x0079: ans = "CODE"; break;
				case 0x007A: ans = "NAMES"; break;
				case 0x007B: ans = "DIRECTORY"; break;
				case 0x007C: ans = "FIND"; break;
				case 0x007D: ans = "CELL"; break;
				case 0x007E: ans = "ISERR"; break;
				case 0x007F: ans = "ISTEXT"; break;
				case 0x0080: ans = "ISNUMBER"; break;
				case 0x0081: ans = "ISBLANK"; break;
				case 0x0082: ans = "T"; break;
				case 0x0083: ans = "N"; break;
				case 0x0084: ans = "FOPEN"; break;
				case 0x0085: ans = "FCLOSE"; break;
				case 0x0086: ans = "FSIZE"; break;
				case 0x0087: ans = "FREADLN"; break;
				case 0x0088: ans = "FREAD"; break;
				case 0x0089: ans = "FWRITELN"; break;
				case 0x008A: ans = "FWRITE"; break;
				case 0x008B: ans = "FPOS"; break;
				case 0x008C: ans = "DATEVALUE"; break;
				case 0x008D: ans = "TIMEVALUE"; break;
				case 0x008E: ans = "SLN"; break;
				case 0x008F: ans = "SYD"; break;
				case 0x0090: ans = "DDB"; break;
				case 0x0091: ans = "GET.DEF"; break;
				case 0x0092: ans = "REFTEXT"; break;
				case 0x0093: ans = "TEXTREF"; break;
				case 0x0094: ans = "INDIRECT"; break;
				case 0x0095: ans = "REGISTER"; break;
				case 0x0096: ans = "CALL"; break;
				case 0x0097: ans = "ADD.BAR"; break;
				case 0x0098: ans = "ADD.MENU"; break;
				case 0x0099: ans = "ADD.COMMAND"; break;
				case 0x009A: ans = "ENABLE.COMMAND"; break;
				case 0x009B: ans = "CHECK.COMMAND"; break;
				case 0x009C: ans = "RENAME.COMMAND"; break;
				case 0x009D: ans = "SHOW.BAR"; break;
				case 0x009E: ans = "DELETE.MENU"; break;
				case 0x009F: ans = "DELETE.COMMAND"; break;
				case 0x00A0: ans = "GET.CHART.ITEM"; break;
				case 0x00A1: ans = "DIALOG.BOX"; break;
				case 0x00A2: ans = "CLEAN"; break;
				case 0x00A3: ans = "MDETERM"; break;
				case 0x00A4: ans = "MINVERSE"; break;
				case 0x00A5: ans = "MMULT"; break;
				case 0x00A6: ans = "FILES"; break;
				case 0x00A7: ans = "IPMT"; break;
				case 0x00A8: ans = "PPMT"; break;
				case 0x00A9: ans = "COUNTA"; break;
				case 0x00AA: ans = "CANCEL.KEY"; break;
				case 0x00AB: ans = "FOR"; break;
				case 0x00AC: ans = "WHILE"; break;
				case 0x00AD: ans = "BREAK"; break;
				case 0x00AE: ans = "NEXT"; break;
				case 0x00AF: ans = "INITIATE"; break;
				case 0x00B0: ans = "REQUEST"; break;
				case 0x00B1: ans = "POKE"; break;
				case 0x00B2: ans = "EXECUTE"; break;
				case 0x00B3: ans = "TERMINATE"; break;
				case 0x00B4: ans = "RESTART"; break;
				case 0x00B5: ans = "HELP"; break;
				case 0x00B6: ans = "GET.BAR"; break;
				case 0x00B7: ans = "PRODUCT"; break;
				case 0x00B8: ans = "FACT"; break;
				case 0x00B9: ans = "GET.CELL"; break;
				case 0x00BA: ans = "GET.WORKSPACE"; break;
				case 0x00BB: ans = "GET.WINDOW"; break;
				case 0x00BC: ans = "GET.DOCUMENT"; break;
				case 0x00BD: ans = "DPRODUCT"; break;
				case 0x00BE: ans = "ISNONTEXT"; break;
				case 0x00BF: ans = "GET.NOTE"; break;
				case 0x00C0: ans = "NOTE"; break;
				case 0x00C1: ans = "STDEVP"; break;
				case 0x00C2: ans = "VARP"; break;
				case 0x00C3: ans = "DSTDEVP"; break;
				case 0x00C4: ans = "DVARP"; break;
				case 0x00C5: ans = "TRUNC"; break;
				case 0x00C6: ans = "ISLOGICAL"; break;
				case 0x00C7: ans = "DCOUNTA"; break;
				case 0x00C8: ans = "DELETE.BAR"; break;
				case 0x00C9: ans = "UNREGISTER"; break;
				case 0x00CC: ans = "USDOLLAR"; break;
				case 0x00CD: ans = "FINDB"; break;
				case 0x00CE: ans = "SEARCHB"; break;
				case 0x00CF: ans = "REPLACEB"; break;
				case 0x00D0: ans = "LEFTB"; break;
				case 0x00D1: ans = "RIGHTB"; break;
				case 0x00D2: ans = "MIDB"; break;
				case 0x00D3: ans = "LENB"; break;
				case 0x00D4: ans = "ROUNDUP"; break;
				case 0x00D5: ans = "ROUNDDOWN"; break;
				case 0x00D6: ans = "ASC"; break;
				case 0x00D7: ans = "DBCS"; break;
				case 0x00D8: ans = "RANK"; break;
				case 0x00DB: ans = "ADDRESS"; break;
				case 0x00DC: ans = "DAYS360"; break;
				case 0x00DD: ans = "TODAY"; break;
				case 0x00DE: ans = "VDB"; break;
				case 0x00DF: ans = "ELSE"; break;
				case 0x00E0: ans = "ELSE.IF"; break;
				case 0x00E1: ans = "END.IF"; break;
				case 0x00E2: ans = "FOR.CELL"; break;
				case 0x00E3: ans = "MEDIAN"; break;
				case 0x00E4: ans = "SUMPRODUCT"; break;
				case 0x00E5: ans = "SINH"; break;
				case 0x00E6: ans = "COSH"; break;
				case 0x00E7: ans = "TANH"; break;
				case 0x00E8: ans = "ASINH"; break;
				case 0x00E9: ans = "ACOSH"; break;
				case 0x00EA: ans = "ATANH"; break;
				case 0x00EB: ans = "DGET"; break;
				case 0x00EC: ans = "CREATE.OBJECT"; break;
				case 0x00ED: ans = "VOLATILE"; break;
				case 0x00EE: ans = "LAST.ERROR"; break;
				case 0x00EF: ans = "CUSTOM.UNDO"; break;
				case 0x00F0: ans = "CUSTOM.REPEAT"; break;
				case 0x00F1: ans = "FORMULA.CONVERT"; break;
				case 0x00F2: ans = "GET.LINK.INFO"; break;
				case 0x00F3: ans = "TEXT.BOX"; break;
				case 0x00F4: ans = "INFO"; break;
				case 0x00F5: ans = "GROUP"; break;
				case 0x00F6: ans = "GET.OBJECT"; break;
				case 0x00F7: ans = "DB"; break;
				case 0x00F8: ans = "PAUSE"; break;
				case 0x00FB: ans = "RESUME"; break;
				case 0x00FC: ans = "FREQUENCY"; break;
				case 0x00FD: ans = "ADD.TOOLBAR"; break;
				case 0x00FE: ans = "DELETE.TOOLBAR"; break;
				case 0x00FF: ans = "User Defined Function"; break;
				case 0x0100: ans = "RESET.TOOLBAR"; break;
				case 0x0101: ans = "EVALUATE"; break;
				case 0x0102: ans = "GET.TOOLBAR"; break;
				case 0x0103: ans = "GET.TOOL"; break;
				case 0x0104: ans = "SPELLING.CHECK"; break;
				case 0x0105: ans = "ERROR.TYPE"; break;
				case 0x0106: ans = "APP.TITLE"; break;
				case 0x0107: ans = "WINDOW.TITLE"; break;
				case 0x0108: ans = "SAVE.TOOLBAR"; break;
				case 0x0109: ans = "ENABLE.TOOL"; break;
				case 0x010A: ans = "PRESS.TOOL"; break;
				case 0x010B: ans = "REGISTER.ID"; break;
				case 0x010C: ans = "GET.WORKBOOK"; break;
				case 0x010D: ans = "AVEDEV"; break;
				case 0x010E: ans = "BETADIST"; break;
				case 0x010F: ans = "GAMMALN"; break;
				case 0x0110: ans = "BETAINV"; break;
				case 0x0111: ans = "BINOMDIST"; break;
				case 0x0112: ans = "CHIDIST"; break;
				case 0x0113: ans = "CHIINV"; break;
				case 0x0114: ans = "COMBIN"; break;
				case 0x0115: ans = "CONFIDENCE"; break;
				case 0x0116: ans = "CRITBINOM"; break;
				case 0x0117: ans = "EVEN"; break;
				case 0x0118: ans = "EXPONDIST"; break;
				case 0x0119: ans = "FDIST"; break;
				case 0x011A: ans = "FINV"; break;
				case 0x011B: ans = "FISHER"; break;
				case 0x011C: ans = "FISHERINV"; break;
				case 0x011D: ans = "FLOOR"; break;
				case 0x011E: ans = "GAMMADIST"; break;
				case 0x011F: ans = "GAMMAINV"; break;
				case 0x0120: ans = "CEILING"; break;
				case 0x0121: ans = "HYPGEOMDIST"; break;
				case 0x0122: ans = "LOGNORMDIST"; break;
				case 0x0123: ans = "LOGINV"; break;
				case 0x0124: ans = "NEGBINOMDIST"; break;
				case 0x0125: ans = "NORMDIST"; break;
				case 0x0126: ans = "NORMSDIST"; break;
				case 0x0127: ans = "NORMINV"; break;
				case 0x0128: ans = "NORMSINV"; break;
				case 0x0129: ans = "STANDARDIZE"; break;
				case 0x012A: ans = "ODD"; break;
				case 0x012B: ans = "PERMUT"; break;
				case 0x012C: ans = "POISSON"; break;
				case 0x012D: ans = "TDIST"; break;
				case 0x012E: ans = "WEIBULL"; break;
				case 0x012F: ans = "SUMXMY2"; break;
				case 0x0130: ans = "SUMX2MY2"; break;
				case 0x0131: ans = "SUMX2PY2"; break;
				case 0x0132: ans = "CHITEST"; break;
				case 0x0133: ans = "CORREL"; break;
				case 0x0134: ans = "COVAR"; break;
				case 0x0135: ans = "FORECAST"; break;
				case 0x0136: ans = "FTEST"; break;
				case 0x0137: ans = "INTERCEPT"; break;
				case 0x0138: ans = "PEARSON"; break;
				case 0x0139: ans = "RSQ"; break;
				case 0x013A: ans = "STEYX"; break;
				case 0x013B: ans = "SLOPE"; break;
				case 0x013C: ans = "TTEST"; break;
				case 0x013D: ans = "PROB"; break;
				case 0x013E: ans = "DEVSQ"; break;
				case 0x013F: ans = "GEOMEAN"; break;
				case 0x0140: ans = "HARMEAN"; break;
				case 0x0141: ans = "SUMSQ"; break;
				case 0x0142: ans = "KURT"; break;
				case 0x0143: ans = "SKEW"; break;
				case 0x0144: ans = "ZTEST"; break;
				case 0x0145: ans = "LARGE"; break;
				case 0x0146: ans = "SMALL"; break;
				case 0x0147: ans = "QUARTILE"; break;
				case 0x0148: ans = "PERCENTILE"; break;
				case 0x0149: ans = "PERCENTRANK"; break;
				case 0x014A: ans = "MODE"; break;
				case 0x014B: ans = "TRIMMEAN"; break;
				case 0x014C: ans = "TINV"; break;
				case 0x014E: ans = "MOVIE.COMMAND"; break;
				case 0x014F: ans = "GET.MOVIE"; break;
				case 0x0150: ans = "CONCATENATE"; break;
				case 0x0151: ans = "POWER"; break;
				case 0x0152: ans = "PIVOT.ADD.DATA"; break;
				case 0x0153: ans = "GET.PIVOT.TABLE"; break;
				case 0x0154: ans = "GET.PIVOT.FIELD"; break;
				case 0x0155: ans = "GET.PIVOT.ITEM"; break;
				case 0x0156: ans = "RADIANS"; break;
				case 0x0157: ans = "DEGREES"; break;
				case 0x0158: ans = "SUBTOTAL"; break;
				case 0x0159: ans = "SUMIF"; break;
				case 0x015A: ans = "COUNTIF"; break;
				case 0x015B: ans = "COUNTBLANK"; break;
				case 0x015C: ans = "SCENARIO.GET"; break;
				case 0x015D: ans = "OPTIONS.LISTS.GET"; break;
				case 0x015E: ans = "ISPMT"; break;
				case 0x015F: ans = "DATEDIF"; break;
				case 0x0160: ans = "DATESTRING"; break;
				case 0x0161: ans = "NUMBERSTRING"; break;
				case 0x0162: ans = "ROMAN"; break;
				case 0x0163: ans = "OPEN.DIALOG"; break;
				case 0x0164: ans = "SAVE.DIALOG"; break;
				case 0x0165: ans = "VIEW.GET"; break;
				case 0x0166: ans = "GETPIVOTDATA"; break;
				case 0x0167: ans = "HYPERLINK"; break;
				case 0x0168: ans = "PHONETIC"; break;
				case 0x0169: ans = "AVERAGEA"; break;
				case 0x016A: ans = "MAXA"; break;
				case 0x016B: ans = "MINA"; break;
				case 0x016C: ans = "STDEVPA"; break;
				case 0x016D: ans = "VARPA"; break;
				case 0x016E: ans = "STDEVA"; break;
				case 0x016F: ans = "VARA"; break;
				case 0x0170: ans = "BAHTTEXT"; break;
				case 0x0171: ans = "THAIDAYOFWEEK"; break;
				case 0x0172: ans = "THAIDIGIT"; break;
				case 0x0173: ans = "THAIMONTHOFYEAR"; break;
				case 0x0174: ans = "THAINUMSOUND"; break;
				case 0x0175: ans = "THAINUMSTRING"; break;
				case 0x0176: ans = "THAISTRINGLENGTH"; break;
				case 0x0177: ans = "ISTHAIDIGIT"; break;
				case 0x0178: ans = "ROUNDBAHTDOWN"; break;
				case 0x0179: ans = "ROUNDBAHTUP"; break;
				case 0x017A: ans = "THAIYEAR"; break;
				case 0x017B: ans = "RTD"; break;
				default: ans = "Unknown_fTab_Function"; break;
				}
				return ans;
			}
			
			/*
			CSV taken from table given here: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/0b8acba5-86d2-4854-836e-0afaee743d44
			Powershell to generate case statements
				$data = Import-Csv -Path $CSVFile_FullPath;
				$data | sort Value |  % { "case " + $_.Value + ": ans = `"" + $_.Meaning + "`"; break;" } | Out-Clipboard
			*/
			std::string GetFunctionName_CeTab(unsigned short cetab) {
				std::string ans;
				switch (cetab) {
				case 0x0000: ans = "BEEP"; break;
				case 0x0001: ans = "OPEN"; break;
				case 0x0002: ans = "OPEN.LINKS"; break;
				case 0x0003: ans = "CLOSE.ALL"; break;
				case 0x0004: ans = "SAVE"; break;
				case 0x0005: ans = "SAVE.AS"; break;
				case 0x0006: ans = "FILE.DELETE"; break;
				case 0x0007: ans = "PAGE.SETUP"; break;
				case 0x0008: ans = "PRINT"; break;
				case 0x0009: ans = "PRINTER.SETUP"; break;
				case 0x000A: ans = "QUIT"; break;
				case 0x000B: ans = "NEW.WINDOW"; break;
				case 0x000C: ans = "ARRANGE.ALL"; break;
				case 0x000D: ans = "WINDOW.SIZE"; break;
				case 0x000E: ans = "WINDOW.MOVE"; break;
				case 0x000F: ans = "FULL"; break;
				case 0x0010: ans = "CLOSE"; break;
				case 0x0011: ans = "RUN"; break;
				case 0x0016: ans = "SET.PRINT.AREA"; break;
				case 0x0017: ans = "SET.PRINT.TITLES"; break;
				case 0x0018: ans = "SET.PAGE.BREAK"; break;
				case 0x0019: ans = "REMOVE.PAGE.BREAK"; break;
				case 0x001A: ans = "FONT"; break;
				case 0x001B: ans = "DISPLAY"; break;
				case 0x001C: ans = "PROTECT.DOCUMENT"; break;
				case 0x001D: ans = "PRECISION"; break;
				case 0x001E: ans = "A1.R1C1"; break;
				case 0x001F: ans = "CALCULATE.NOW"; break;
				case 0x0020: ans = "CALCULATION"; break;
				case 0x0022: ans = "DATA.FIND"; break;
				case 0x0023: ans = "EXTRACT"; break;
				case 0x0024: ans = "DATA.DELETE"; break;
				case 0x0025: ans = "SET.DATABASE"; break;
				case 0x0026: ans = "SET.CRITERIA"; break;
				case 0x0027: ans = "SORT"; break;
				case 0x0028: ans = "DATA.SERIES"; break;
				case 0x0029: ans = "TABLE"; break;
				case 0x002A: ans = "FORMAT.NUMBER"; break;
				case 0x002B: ans = "ALIGNMENT"; break;
				case 0x002C: ans = "STYLE"; break;
				case 0x002D: ans = "BORDER"; break;
				case 0x002E: ans = "CELL.PROTECTION"; break;
				case 0x002F: ans = "COLUMN.WIDTH"; break;
				case 0x0030: ans = "UNDO"; break;
				case 0x0031: ans = "CUT"; break;
				case 0x0032: ans = "COPY"; break;
				case 0x0033: ans = "PASTE"; break;
				case 0x0034: ans = "CLEAR"; break;
				case 0x0035: ans = "PASTE.SPECIAL"; break;
				case 0x0036: ans = "EDIT.DELETE"; break;
				case 0x0037: ans = "INSERT"; break;
				case 0x0038: ans = "FILL.RIGHT"; break;
				case 0x0039: ans = "FILL.DOWN"; break;
				case 0x003D: ans = "DEFINE.NAME"; break;
				case 0x003E: ans = "CREATE.NAMES"; break;
				case 0x003F: ans = "FORMULA.GOTO"; break;
				case 0x0040: ans = "FORMULA.FIND"; break;
				case 0x0041: ans = "SELECT.LAST.CELL"; break;
				case 0x0042: ans = "SHOW.ACTIVE.CELL"; break;
				case 0x0043: ans = "GALLERY.AREA"; break;
				case 0x0044: ans = "GALLERY.BAR"; break;
				case 0x0045: ans = "GALLERY.COLUMN"; break;
				case 0x0046: ans = "GALLERY.LINE"; break;
				case 0x0047: ans = "GALLERY.PIE"; break;
				case 0x0048: ans = "GALLERY.SCATTER"; break;
				case 0x0049: ans = "COMBINATION"; break;
				case 0x004A: ans = "PREFERRED"; break;
				case 0x004B: ans = "ADD.OVERLAY"; break;
				case 0x004C: ans = "GRIDLINES"; break;
				case 0x004D: ans = "SET.PREFERRED"; break;
				case 0x004E: ans = "AXES"; break;
				case 0x004F: ans = "LEGEND"; break;
				case 0x0050: ans = "ATTACH.TEXT"; break;
				case 0x0051: ans = "ADD.ARROW"; break;
				case 0x0052: ans = "SELECT.CHART"; break;
				case 0x0053: ans = "SELECT.PLOT.AREA"; break;
				case 0x0054: ans = "PATTERNS"; break;
				case 0x0055: ans = "MAIN.CHART"; break;
				case 0x0056: ans = "OVERLAY"; break;
				case 0x0057: ans = "SCALE"; break;
				case 0x0058: ans = "FORMAT.LEGEND"; break;
				case 0x0059: ans = "FORMAT.TEXT"; break;
				case 0x005A: ans = "EDIT.REPEAT"; break;
				case 0x005B: ans = "PARSE"; break;
				case 0x005C: ans = "JUSTIFY"; break;
				case 0x005D: ans = "HIDE"; break;
				case 0x005E: ans = "UNHIDE"; break;
				case 0x005F: ans = "WORKSPACE"; break;
				case 0x0060: ans = "FORMULA"; break;
				case 0x0061: ans = "FORMULA.FILL"; break;
				case 0x0062: ans = "FORMULA.ARRAY"; break;
				case 0x0063: ans = "DATA.FIND.NEXT"; break;
				case 0x0064: ans = "DATA.FIND.PREV"; break;
				case 0x0065: ans = "FORMULA.FIND.NEXT"; break;
				case 0x0066: ans = "FORMULA.FIND.PREV"; break;
				case 0x0067: ans = "ACTIVATE"; break;
				case 0x0068: ans = "ACTIVATE.NEXT"; break;
				case 0x0069: ans = "ACTIVATE.PREV"; break;
				case 0x006A: ans = "UNLOCKED.NEXT"; break;
				case 0x006B: ans = "UNLOCKED.PREV"; break;
				case 0x006C: ans = "COPY.PICTURE"; break;
				case 0x006D: ans = "SELECT"; break;
				case 0x006E: ans = "DELETE.NAME"; break;
				case 0x006F: ans = "DELETE.FORMAT"; break;
				case 0x0070: ans = "VLINE"; break;
				case 0x0071: ans = "HLINE"; break;
				case 0x0072: ans = "VPAGE"; break;
				case 0x0073: ans = "HPAGE"; break;
				case 0x0074: ans = "VSCROLL"; break;
				case 0x0075: ans = "HSCROLL"; break;
				case 0x0076: ans = "ALERT"; break;
				case 0x0077: ans = "NEW"; break;
				case 0x0078: ans = "CANCEL.COPY"; break;
				case 0x0079: ans = "SHOW.CLIPBOARD"; break;
				case 0x007A: ans = "MESSAGE"; break;
				case 0x007C: ans = "PASTE.LINK"; break;
				case 0x007D: ans = "APP.ACTIVATE"; break;
				case 0x007E: ans = "DELETE.ARROW"; break;
				case 0x007F: ans = "ROW.HEIGHT"; break;
				case 0x0080: ans = "FORMAT.MOVE"; break;
				case 0x0081: ans = "FORMAT.SIZE"; break;
				case 0x0082: ans = "FORMULA.REPLACE"; break;
				case 0x0083: ans = "SEND.KEYS"; break;
				case 0x0084: ans = "SELECT.SPECIAL"; break;
				case 0x0085: ans = "APPLY.NAMES"; break;
				case 0x0086: ans = "REPLACE.FONT"; break;
				case 0x0087: ans = "FREEZE.PANES"; break;
				case 0x0088: ans = "SHOW.INFO"; break;
				case 0x0089: ans = "SPLIT"; break;
				case 0x008A: ans = "ON.WINDOW"; break;
				case 0x008B: ans = "ON.DATA"; break;
				case 0x008C: ans = "DISABLE.INPUT"; break;
				case 0x008E: ans = "OUTLINE"; break;
				case 0x008F: ans = "LIST.NAMES"; break;
				case 0x0090: ans = "FILE.CLOSE"; break;
				case 0x0091: ans = "SAVE.WORKBOOK"; break;
				case 0x0092: ans = "DATA.FORM"; break;
				case 0x0093: ans = "COPY.CHART"; break;
				case 0x0094: ans = "ON.TIME"; break;
				case 0x0095: ans = "WAIT"; break;
				case 0x0096: ans = "FORMAT.FONT"; break;
				case 0x0097: ans = "FILL.UP"; break;
				case 0x0098: ans = "FILL.LEFT"; break;
				case 0x0099: ans = "DELETE.OVERLAY"; break;
				case 0x009B: ans = "SHORT.MENUS"; break;
				case 0x009F: ans = "SET.UPDATE.STATUS"; break;
				case 0x00A1: ans = "COLOR.PALETTE"; break;
				case 0x00A2: ans = "DELETE.STYLE"; break;
				case 0x00A3: ans = "WINDOW.RESTORE"; break;
				case 0x00A4: ans = "WINDOW.MAXIMIZE"; break;
				case 0x00A6: ans = "CHANGE.LINK"; break;
				case 0x00A7: ans = "CALCULATE.DOCUMENT"; break;
				case 0x00A8: ans = "ON.KEY"; break;
				case 0x00A9: ans = "APP.RESTORE"; break;
				case 0x00AA: ans = "APP.MOVE"; break;
				case 0x00AB: ans = "APP.SIZE"; break;
				case 0x00AC: ans = "APP.MINIMIZE"; break;
				case 0x00AD: ans = "APP.MAXIMIZE"; break;
				case 0x00AE: ans = "BRING.TO.FRONT"; break;
				case 0x00AF: ans = "SEND.TO.BACK"; break;
				case 0x00B9: ans = "MAIN.CHART.TYPE"; break;
				case 0x00BA: ans = "OVERLAY.CHART.TYPE"; break;
				case 0x00BB: ans = "SELECT.END"; break;
				case 0x00BC: ans = "OPEN.MAIL"; break;
				case 0x00BD: ans = "SEND.MAIL"; break;
				case 0x00BE: ans = "STANDARD.FONT"; break;
				case 0x00BF: ans = "CONSOLIDATE"; break;
				case 0x00C0: ans = "SORT.SPECIAL"; break;
				case 0x00C1: ans = "GALLERY.3D.AREA"; break;
				case 0x00C2: ans = "GALLERY.3D.COLUMN"; break;
				case 0x00C3: ans = "GALLERY.3D.LINE"; break;
				case 0x00C4: ans = "GALLERY.3D.PIE"; break;
				case 0x00C5: ans = "VIEW.3D"; break;
				case 0x00C6: ans = "GOAL.SEEK"; break;
				case 0x00C7: ans = "WORKGROUP"; break;
				case 0x00C8: ans = "FILL.GROUP"; break;
				case 0x00C9: ans = "UPDATE.LINK"; break;
				case 0x00CA: ans = "PROMOTE"; break;
				case 0x00CB: ans = "DEMOTE"; break;
				case 0x00CC: ans = "SHOW.DETAIL"; break;
				case 0x00CE: ans = "UNGROUP"; break;
				case 0x00CF: ans = "OBJECT.PROPERTIES"; break;
				case 0x00D0: ans = "SAVE.NEW.OBJECT"; break;
				case 0x00D1: ans = "SHARE"; break;
				case 0x00D2: ans = "SHARE.NAME"; break;
				case 0x00D3: ans = "DUPLICATE"; break;
				case 0x00D4: ans = "APPLY.STYLE"; break;
				case 0x00D5: ans = "ASSIGN.TO.OBJECT"; break;
				case 0x00D6: ans = "OBJECT.PROTECTION"; break;
				case 0x00D7: ans = "HIDE.OBJECT"; break;
				case 0x00D8: ans = "SET.EXTRACT"; break;
				case 0x00D9: ans = "CREATE.PUBLISHER"; break;
				case 0x00DA: ans = "SUBSCRIBE.TO"; break;
				case 0x00DB: ans = "ATTRIBUTES"; break;
				case 0x00DC: ans = "SHOW.TOOLBAR"; break;
				case 0x00DE: ans = "PRINT.PREVIEW"; break;
				case 0x00DF: ans = "EDIT.COLOR"; break;
				case 0x00E0: ans = "SHOW.LEVELS"; break;
				case 0x00E1: ans = "FORMAT.MAIN"; break;
				case 0x00E2: ans = "FORMAT.OVERLAY"; break;
				case 0x00E3: ans = "ON.RECALC"; break;
				case 0x00E4: ans = "EDIT.SERIES"; break;
				case 0x00E5: ans = "DEFINE.STYLE"; break;
				case 0x00F0: ans = "LINE.PRINT"; break;
				case 0x00F3: ans = "ENTER.DATA"; break;
				case 0x00F9: ans = "GALLERY.RADAR"; break;
				case 0x00FA: ans = "MERGE.STYLES"; break;
				case 0x00FB: ans = "EDITION.OPTIONS"; break;
				case 0x00FC: ans = "PASTE.PICTURE"; break;
				case 0x00FD: ans = "PASTE.PICTURE.LINK"; break;
				case 0x00FE: ans = "SPELLING"; break;
				case 0x0100: ans = "ZOOM"; break;
				case 0x0103: ans = "INSERT.OBJECT"; break;
				case 0x0104: ans = "WINDOW.MINIMIZE"; break;
				case 0x0109: ans = "SOUND.NOTE"; break;
				case 0x010A: ans = "SOUND.PLAY"; break;
				case 0x010B: ans = "FORMAT.SHAPE"; break;
				case 0x010C: ans = "EXTEND.POLYGON"; break;
				case 0x010D: ans = "FORMAT.AUTO"; break;
				case 0x0110: ans = "GALLERY.3D.BAR"; break;
				case 0x0111: ans = "GALLERY.3D.SURFACE"; break;
				case 0x0112: ans = "FILL.AUTO"; break;
				case 0x0114: ans = "CUSTOMIZE.TOOLBAR"; break;
				case 0x0115: ans = "ADD.TOOL"; break;
				case 0x0116: ans = "EDIT.OBJECT"; break;
				case 0x0117: ans = "ON.DOUBLECLICK"; break;
				case 0x0118: ans = "ON.ENTRY"; break;
				case 0x0119: ans = "WORKBOOK.ADD"; break;
				case 0x011A: ans = "WORKBOOK.MOVE"; break;
				case 0x011B: ans = "WORKBOOK.COPY"; break;
				case 0x011C: ans = "WORKBOOK.OPTIONS"; break;
				case 0x011D: ans = "SAVE.WORKSPACE"; break;
				case 0x0120: ans = "CHART.WIZARD"; break;
				case 0x0121: ans = "DELETE.TOOL"; break;
				case 0x0122: ans = "MOVE.TOOL"; break;
				case 0x0123: ans = "WORKBOOK.SELECT"; break;
				case 0x0124: ans = "WORKBOOK.ACTIVATE"; break;
				case 0x0125: ans = "ASSIGN.TO.TOOL"; break;
				case 0x0127: ans = "COPY.TOOL"; break;
				case 0x0128: ans = "RESET.TOOL"; break;
				case 0x0129: ans = "CONSTRAIN.NUMERIC"; break;
				case 0x012A: ans = "PASTE.TOOL"; break;
				case 0x012E: ans = "WORKBOOK.NEW"; break;
				case 0x0131: ans = "SCENARIO.CELLS"; break;
				case 0x0132: ans = "SCENARIO.DELETE"; break;
				case 0x0133: ans = "SCENARIO.ADD"; break;
				case 0x0134: ans = "SCENARIO.EDIT"; break;
				case 0x0135: ans = "SCENARIO.SHOW"; break;
				case 0x0136: ans = "SCENARIO.SHOW.NEXT"; break;
				case 0x0137: ans = "SCENARIO.SUMMARY"; break;
				case 0x0138: ans = "PIVOT.TABLE.WIZARD"; break;
				case 0x0139: ans = "PIVOT.FIELD.PROPERTIES"; break;
				case 0x013A: ans = "PIVOT.FIELD"; break;
				case 0x013B: ans = "PIVOT.ITEM"; break;
				case 0x013C: ans = "PIVOT.ADD.FIELDS"; break;
				case 0x013E: ans = "OPTIONS.CALCULATION"; break;
				case 0x013F: ans = "OPTIONS.EDIT"; break;
				case 0x0140: ans = "OPTIONS.VIEW"; break;
				case 0x0141: ans = "ADDIN.MANAGER"; break;
				case 0x0142: ans = "MENU.EDITOR"; break;
				case 0x0143: ans = "ATTACH.TOOLBARS"; break;
				case 0x0144: ans = "VBAActivate"; break;
				case 0x0145: ans = "OPTIONS.CHART"; break;
				case 0x0148: ans = "VBA.INSERT.FILE"; break;
				case 0x014A: ans = "VBA.PROCEDURE.DEFINITION"; break;
				case 0x0150: ans = "ROUTING.SLIP"; break;
				case 0x0152: ans = "ROUTE.DOCUMENT"; break;
				case 0x0153: ans = "MAIL.LOGON"; break;
				case 0x0156: ans = "INSERT.PICTURE"; break;
				case 0x0157: ans = "EDIT.TOOL"; break;
				case 0x0158: ans = "GALLERY.DOUGHNUT"; break;
				case 0x015E: ans = "CHART.TREND"; break;
				case 0x0160: ans = "PIVOT.ITEM.PROPERTIES"; break;
				case 0x0162: ans = "WORKBOOK.INSERT"; break;
				case 0x0163: ans = "OPTIONS.TRANSITION"; break;
				case 0x0164: ans = "OPTIONS.GENERAL"; break;
				case 0x0172: ans = "FILTER.ADVANCED"; break;
				case 0x0175: ans = "MAIL.ADD.MAILER"; break;
				case 0x0176: ans = "MAIL.DELETE.MAILER"; break;
				case 0x0177: ans = "MAIL.REPLY"; break;
				case 0x0178: ans = "MAIL.REPLY.ALL"; break;
				case 0x0179: ans = "MAIL.FORWARD"; break;
				case 0x017A: ans = "MAIL.NEXT.LETTER"; break;
				case 0x017B: ans = "DATA.LABEL"; break;
				case 0x017C: ans = "INSERT.TITLE"; break;
				case 0x017D: ans = "FONT.PROPERTIES"; break;
				case 0x017E: ans = "MACRO.OPTIONS"; break;
				case 0x017F: ans = "WORKBOOK.HIDE"; break;
				case 0x0180: ans = "WORKBOOK.UNHIDE"; break;
				case 0x0181: ans = "WORKBOOK.DELETE"; break;
				case 0x0182: ans = "WORKBOOK.NAME"; break;
				case 0x0184: ans = "GALLERY.CUSTOM"; break;
				case 0x0186: ans = "ADD.CHART.AUTOFORMAT"; break;
				case 0x0187: ans = "DELETE.CHART.AUTOFORMAT"; break;
				case 0x0188: ans = "CHART.ADD.DATA"; break;
				case 0x0189: ans = "AUTO.OUTLINE"; break;
				case 0x018A: ans = "TAB.ORDER"; break;
				case 0x018B: ans = "SHOW.DIALOG"; break;
				case 0x018C: ans = "SELECT.ALL"; break;
				case 0x018D: ans = "UNGROUP.SHEETS"; break;
				case 0x018E: ans = "SUBTOTAL.CREATE"; break;
				case 0x018F: ans = "SUBTOTAL.REMOVE"; break;
				case 0x0190: ans = "RENAME.OBJECT"; break;
				case 0x019C: ans = "WORKBOOK.SCROLL"; break;
				case 0x019D: ans = "WORKBOOK.NEXT"; break;
				case 0x019E: ans = "WORKBOOK.PREV"; break;
				case 0x019F: ans = "WORKBOOK.TAB.SPLIT"; break;
				case 0x01A0: ans = "FULL.SCREEN"; break;
				case 0x01A1: ans = "WORKBOOK.PROTECT"; break;
				case 0x01A4: ans = "SCROLLBAR.PROPERTIES"; break;
				case 0x01A5: ans = "PIVOT.SHOW.PAGES"; break;
				case 0x01A6: ans = "TEXT.TO.COLUMNS"; break;
				case 0x01A7: ans = "FORMAT.CHARTTYPE"; break;
				case 0x01A8: ans = "LINK.FORMAT"; break;
				case 0x01A9: ans = "TRACER.DISPLAY"; break;
				case 0x01AE: ans = "TRACER.NAVIGATE"; break;
				case 0x01AF: ans = "TRACER.CLEAR"; break;
				case 0x01B0: ans = "TRACER.ERROR"; break;
				case 0x01B1: ans = "PIVOT.FIELD.GROUP"; break;
				case 0x01B2: ans = "PIVOT.FIELD.UNGROUP"; break;
				case 0x01B3: ans = "CHECKBOX.PROPERTIES"; break;
				case 0x01B4: ans = "LABEL.PROPERTIES"; break;
				case 0x01B5: ans = "LISTBOX.PROPERTIES"; break;
				case 0x01B6: ans = "EDITBOX.PROPERTIES"; break;
				case 0x01B7: ans = "PIVOT.REFRESH"; break;
				case 0x01B8: ans = "LINK.COMBO"; break;
				case 0x01B9: ans = "OPEN.TEXT"; break;
				case 0x01BA: ans = "HIDE.DIALOG"; break;
				case 0x01BB: ans = "SET.DIALOG.FOCUS"; break;
				case 0x01BC: ans = "ENABLE.OBJECT"; break;
				case 0x01BD: ans = "PUSHBUTTON.PROPERTIES"; break;
				case 0x01BE: ans = "SET.DIALOG.DEFAULT"; break;
				case 0x01BF: ans = "FILTER"; break;
				case 0x01C0: ans = "FILTER.SHOW.ALL"; break;
				case 0x01C1: ans = "CLEAR.OUTLINE"; break;
				case 0x01C2: ans = "FUNCTION.WIZARD"; break;
				case 0x01C3: ans = "ADD.LIST.ITEM"; break;
				case 0x01C4: ans = "SET.LIST.ITEM"; break;
				case 0x01C5: ans = "REMOVE.LIST.ITEM"; break;
				case 0x01C6: ans = "SELECT.LIST.ITEM"; break;
				case 0x01C7: ans = "SET.CONTROL.VALUE"; break;
				case 0x01C8: ans = "SAVE.COPY.AS"; break;
				case 0x01CA: ans = "OPTIONS.LISTS.ADD"; break;
				case 0x01CB: ans = "OPTIONS.LISTS.DELETE"; break;
				case 0x01CC: ans = "SERIES.AXES"; break;
				case 0x01CD: ans = "SERIES.X"; break;
				case 0x01CE: ans = "SERIES.Y"; break;
				case 0x01CF: ans = "ERRORBAR.X"; break;
				case 0x01D0: ans = "ERRORBAR.Y"; break;
				case 0x01D1: ans = "FORMAT.CHART"; break;
				case 0x01D2: ans = "SERIES.ORDER"; break;
				case 0x01D3: ans = "MAIL.LOGOFF"; break;
				case 0x01D4: ans = "CLEAR.ROUTING.SLIP"; break;
				case 0x01D5: ans = "APP.ACTIVATE.MICROSOFT"; break;
				case 0x01D6: ans = "MAIL.EDIT.MAILER"; break;
				case 0x01D7: ans = "ON.SHEET"; break;
				case 0x01D8: ans = "STANDARD.WIDTH"; break;
				case 0x01D9: ans = "SCENARIO.MERGE"; break;
				case 0x01DA: ans = "SUMMARY.INFO"; break;
				case 0x01DB: ans = "FIND.FILE"; break;
				case 0x01DC: ans = "ACTIVE.CELL.FONT"; break;
				case 0x01DD: ans = "ENABLE.TIPWIZARD"; break;
				case 0x01DE: ans = "VBA.MAKE.ADDIN"; break;
				case 0x01E0: ans = "INSERTDATATABLE"; break;
				case 0x01E1: ans = "WORKGROUP.OPTIONS"; break;
				case 0x01E2: ans = "MAIL.SEND.MAILER"; break;
				case 0x01E5: ans = "AUTOCORRECT"; break;
				case 0x01E9: ans = "POST.DOCUMENT"; break;
				case 0x01EB: ans = "PICKLIST"; break;
				case 0x01ED: ans = "VIEW.SHOW"; break;
				case 0x01EE: ans = "VIEW.DEFINE"; break;
				case 0x01EF: ans = "VIEW.DELETE"; break;
				case 0x01FD: ans = "SHEET.BACKGROUND"; break;
				case 0x01FE: ans = "INSERT.MAP.OBJECT"; break;
				case 0x01FF: ans = "OPTIONS.MENONO"; break;
				case 0x0205: ans = "MSOCHECKS"; break;
				case 0x0206: ans = "NORMAL"; break;
				case 0x0207: ans = "LAYOUT"; break;
				case 0x0208: ans = "RM.PRINT.AREA"; break;
				case 0x0209: ans = "CLEAR.PRINT.AREA"; break;
				case 0x020A: ans = "ADD.PRINT.AREA"; break;
				case 0x020B: ans = "MOVE.BRK"; break;
				case 0x0221: ans = "HIDECURR.NOTE"; break;
				case 0x0222: ans = "HIDEALL.NOTES"; break;
				case 0x0223: ans = "DELETE.NOTE"; break;
				case 0x0224: ans = "TRAVERSE.NOTES"; break;
				case 0x0225: ans = "ACTIVATE.NOTES"; break;
				case 0x026C: ans = "PROTECT.REVISIONS"; break;
				case 0x026D: ans = "UNPROTECT.REVISIONS"; break;
				case 0x0287: ans = "OPTIONS.ME"; break;
				case 0x028D: ans = "WEB.PUBLISH"; break;
				case 0x029B: ans = "NEWWEBQUERY"; break;
				case 0x02A1: ans = "PIVOT.TABLE.CHART"; break;
				case 0x02F1: ans = "OPTIONS.SAVE"; break;
				case 0x02F3: ans = "OPTIONS.SPELL"; break;
				case 0x0328: ans = "HIDEALL.INKANNOTS"; break;
				default: ans = "Unknown_CeTab_Function"; break;
				}
				return ans;
			}
		}
	}
}
