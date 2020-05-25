#pragma once

#include "Record.hpp"
#include "Records.hpp"


namespace oless {
	namespace excel {
		namespace records {

			/*
			CSV taken from table given here: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/7d9326d6-691a-4fa1-8dce-42082f38e943
			Powershell to generate case statements
				$data = Import-Csv -Path $CSVFile_FullPath;
				$data | % { $_.RecordType = [int]$_.RecordType };
				$data | sort RecordType | % { "case " + "0x{0:X4}" -f ([int]$_.RecordType) + ": r = (Record*)(new " + $_.Name +"Record(type, data)); break;"  } | Out-Clipboard
			*/
			//ParseRecord - parses XLS records according to format
			Record* ParseRecord(unsigned short type, std::vector<uint8_t> data, unsigned short version, IRecordParser* parser) {
				Record* r = nullptr;


				try {
					switch (version) {
					case 1536: { // BIFF8
						switch (type) {
						case 0x0006: r = (Record*)(new FormulaRecord(parser, type, data)); break;
						case 0x000A: r = (Record*)(new EOFRecord(type, data)); break;
						case 0x000C: r = (Record*)(new CalcCountRecord(type, data)); break;
						case 0x000D: r = (Record*)(new CalcModeRecord(type, data)); break;
						case 0x000E: r = (Record*)(new CalcPrecisionRecord(type, data)); break;
						case 0x000F: r = (Record*)(new CalcRefModeRecord(type, data)); break;
						case 0x0010: r = (Record*)(new CalcDeltaRecord(type, data)); break;
						case 0x0011: r = (Record*)(new CalcIterRecord(type, data)); break;
						case 0x0012: r = (Record*)(new ProtectRecord(type, data)); break;
						case 0x0013: r = (Record*)(new PasswordRecord(type, data)); break;
						case 0x0014: r = (Record*)(new HeaderRecord(type, data)); break;
						case 0x0015: r = (Record*)(new FooterRecord(type, data)); break;
						case 0x0017: r = (Record*)(new ExternSheetRecord(type, data)); break;
						case 0x0018: r = (Record*)(new LblRecord(parser, type, data)); break;
						case 0x0019: r = (Record*)(new WinProtectRecord(type, data)); break;
						case 0x001A: r = (Record*)(new VerticalPageBreaksRecord(type, data)); break;
						case 0x001B: r = (Record*)(new HorizontalPageBreaksRecord(type, data)); break;
						case 0x001C: r = (Record*)(new NoteRecord(type, data)); break;
						case 0x001D: r = (Record*)(new SelectionRecord(type, data)); break;
						case 0x0022: r = (Record*)(new Date1904Record(type, data)); break;
						case 0x0023: r = (Record*)(new ExternNameRecord(parser, type, data)); break;
						case 0x0026: r = (Record*)(new LeftMarginRecord(type, data)); break;
						case 0x0027: r = (Record*)(new RightMarginRecord(type, data)); break;
						case 0x0028: r = (Record*)(new TopMarginRecord(type, data)); break;
						case 0x0029: r = (Record*)(new BottomMarginRecord(type, data)); break;
						case 0x002A: r = (Record*)(new PrintRowColRecord(type, data)); break;
						case 0x002B: r = (Record*)(new PrintGridRecord(type, data)); break;
						case 0x002F: r = (Record*)(new FilePassRecord(type, data)); break;
						case 0x0031: r = (Record*)(new FontRecord(type, data)); break;
						case 0x0033: r = (Record*)(new PrintSizeRecord(type, data)); break;
						case 0x003C: r = (Record*)(new ContinueRecord(parser, type, data)); break;
						case 0x003D: r = (Record*)(new Window1Record(type, data)); break;
						case 0x0040: r = (Record*)(new BackupRecord(type, data)); break;
						case 0x0041: r = (Record*)(new PaneRecord(type, data)); break;
						case 0x0042: r = (Record*)(new CodePageRecord(type, data)); break;
						case 0x004D: r = (Record*)(new PlsRecord(type, data)); break;
						case 0x0050: r = (Record*)(new DConRecord(type, data)); break;
						case 0x0051: r = (Record*)(new DConRefRecord(type, data)); break;
						case 0x0052: r = (Record*)(new DConNameRecord(type, data)); break;
						case 0x0055: r = (Record*)(new DefColWidthRecord(type, data)); break;
						case 0x0059: r = (Record*)(new XCTRecord(type, data)); break;
						case 0x005A: r = (Record*)(new CRNRecord(type, data)); break;
						case 0x005B: r = (Record*)(new FileSharingRecord(type, data)); break;
						case 0x005C: r = (Record*)(new WriteAccessRecord(type, data)); break;
						case 0x005D: r = (Record*)(new ObjRecord(type, data)); break;
						case 0x005E: r = (Record*)(new UncalcedRecord(type, data)); break;
						case 0x005F: r = (Record*)(new CalcSaveRecalcRecord(type, data)); break;
						case 0x0060: r = (Record*)(new TemplateRecord(type, data)); break;
						case 0x0061: r = (Record*)(new IntlRecord(type, data)); break;
						case 0x0063: r = (Record*)(new ObjProtectRecord(type, data)); break;
						case 0x007D: r = (Record*)(new ColInfoRecord(type, data)); break;
						case 0x0080: r = (Record*)(new GutsRecord(type, data)); break;
						case 0x0081: r = (Record*)(new WsBoolRecord(type, data)); break;
						case 0x0082: r = (Record*)(new GridSetRecord(type, data)); break;
						case 0x0083: r = (Record*)(new HCenterRecord(type, data)); break;
						case 0x0084: r = (Record*)(new VCenterRecord(type, data)); break;
						case 0x0085: {
							r = (Record*)(new BoundSheet8Record(type, data));
							break;
						}
						case 0x0086: r = (Record*)(new WriteProtectRecord(type, data)); break;
						case 0x008C: r = (Record*)(new CountryRecord(type, data)); break;
						case 0x008D: r = (Record*)(new HideObjRecord(type, data)); break;
						case 0x0090: r = (Record*)(new SortRecord(type, data)); break;
						case 0x0092: r = (Record*)(new PaletteRecord(type, data)); break;
						case 0x0097: r = (Record*)(new SyncRecord(type, data)); break;
						case 0x0098: r = (Record*)(new LPrRecord(type, data)); break;
						case 0x0099: r = (Record*)(new DxGColRecord(type, data)); break;
						case 0x009A: r = (Record*)(new FnGroupNameRecord(type, data)); break;
						case 0x009B: r = (Record*)(new FilterModeRecord(type, data)); break;
						case 0x009C: r = (Record*)(new BuiltInFnGroupCountRecord(type, data)); break;
						case 0x009D: r = (Record*)(new AutoFilterInfoRecord(type, data)); break;
						case 0x009E: r = (Record*)(new AutoFilterRecord(type, data)); break;
						case 0x00A0: r = (Record*)(new SclRecord(type, data)); break;
						case 0x00A1: r = (Record*)(new SetupRecord(type, data)); break;
						case 0x00AE: r = (Record*)(new ScenManRecord(type, data)); break;
						case 0x00AF: r = (Record*)(new SCENARIORecord(type, data)); break;
						case 0x00B0: r = (Record*)(new SxViewRecord(type, data)); break;
						case 0x00B1: r = (Record*)(new SxvdRecord(type, data)); break;
						case 0x00B2: r = (Record*)(new SXVIRecord(type, data)); break;
						case 0x00B4: r = (Record*)(new SxIvdRecord(type, data)); break;
						case 0x00B5: r = (Record*)(new SXLIRecord(type, data)); break;
						case 0x00B6: r = (Record*)(new SXPIRecord(type, data)); break;
						case 0x00B8: r = (Record*)(new DocRouteRecord(type, data)); break;
						case 0x00B9: r = (Record*)(new RecipNameRecord(type, data)); break;
						case 0x00BD: r = (Record*)(new MulRkRecord(type, data)); break;
						case 0x00BE: r = (Record*)(new MulBlankRecord(type, data)); break;
						case 0x00C1: r = (Record*)(new MmsRecord(type, data)); break;
						case 0x00C5: r = (Record*)(new SXDIRecord(type, data)); break;
						case 0x00C6: r = (Record*)(new SXDBRecord(type, data)); break;
						case 0x00C7: r = (Record*)(new SXFDBRecord(type, data)); break;
						case 0x00C8: r = (Record*)(new SXDBBRecord(type, data)); break;
						case 0x00C9: r = (Record*)(new SXNumRecord(type, data)); break;
						case 0x00CA: r = (Record*)(new SxBoolRecord(type, data)); break;
						case 0x00CB: r = (Record*)(new SxErrRecord(type, data)); break;
						case 0x00CC: r = (Record*)(new SXIntRecord(type, data)); break;
						case 0x00CD: r = (Record*)(new SXStringRecord(type, data)); break;
						case 0x00CE: r = (Record*)(new SXDtrRecord(type, data)); break;
						case 0x00CF: r = (Record*)(new SxNilRecord(type, data)); break;
						case 0x00D0: r = (Record*)(new SXTblRecord(type, data)); break;
						case 0x00D1: r = (Record*)(new SXTBRGIITMRecord(type, data)); break;
						case 0x00D2: r = (Record*)(new SxTbpgRecord(type, data)); break;
						case 0x00D3: r = (Record*)(new ObProjRecord(type, data)); break;
						case 0x00D5: r = (Record*)(new SXStreamIDRecord(type, data)); break;
						case 0x00D7: r = (Record*)(new DBCellRecord(type, data)); break;
						case 0x00D8: r = (Record*)(new SXRngRecord(type, data)); break;
						case 0x00D9: r = (Record*)(new SxIsxoperRecord(type, data)); break;
						case 0x00DA: r = (Record*)(new BookBoolRecord(type, data)); break;
						case 0x00DC: r = (Record*)(new DbOrParamQryRecord(type, data)); break;
						case 0x00DD: r = (Record*)(new ScenarioProtectRecord(type, data)); break;
						case 0x00DE: r = (Record*)(new OleObjectSizeRecord(type, data)); break;
						case 0x00E0: r = (Record*)(new XFRecord(type, data)); break;
						case 0x00E1: r = (Record*)(new InterfaceHdrRecord(type, data)); break;
						case 0x00E2: r = (Record*)(new InterfaceEndRecord(type, data)); break;
						case 0x00E3: r = (Record*)(new SXVSRecord(type, data)); break;
						case 0x00E5: r = (Record*)(new MergeCellsRecord(type, data)); break;
						case 0x00E9: r = (Record*)(new BkHimRecord(type, data)); break;
						case 0x00EB: r = (Record*)(new MsoDrawingGroupRecord(type, data)); break;
						case 0x00EC: r = (Record*)(new MsoDrawingRecord(type, data)); break;
						case 0x00ED: r = (Record*)(new MsoDrawingSelectionRecord(type, data)); break;
						case 0x00EF: r = (Record*)(new PhoneticInfoRecord(type, data)); break;
						case 0x00F0: r = (Record*)(new SxRuleRecord(type, data)); break;
						case 0x00F1: r = (Record*)(new SXExRecord(type, data)); break;
						case 0x00F2: r = (Record*)(new SxFiltRecord(type, data)); break;
						case 0x00F4: r = (Record*)(new SxDXFRecord(type, data)); break;
						case 0x00F5: r = (Record*)(new SxItmRecord(type, data)); break;
						case 0x00F6: r = (Record*)(new SxNameRecord(type, data)); break;
						case 0x00F7: r = (Record*)(new SxSelectRecord(type, data)); break;
						case 0x00F8: r = (Record*)(new SXPairRecord(type, data)); break;
						case 0x00F9: r = (Record*)(new SxFmlaRecord(type, data)); break;
						case 0x00FB: r = (Record*)(new SxFormatRecord(type, data)); break;
						case 0x00FC: r = (Record*)(new SSTRecord(type, data)); break;
						case 0x00FD: r = (Record*)(new LabelSstRecord(parser, type, data)); break;
						case 0x00FF: r = (Record*)(new ExtSSTRecord(type, data)); break;
						case 0x0100: r = (Record*)(new SXVDExRecord(type, data)); break;
						case 0x0103: r = (Record*)(new SXFormulaRecord(type, data)); break;
						case 0x0122: r = (Record*)(new SXDBExRecord(type, data)); break;
						case 0x0137: r = (Record*)(new RRDInsDelRecord(type, data)); break;
						case 0x0138: r = (Record*)(new RRDHeadRecord(type, data)); break;
						case 0x013B: r = (Record*)(new RRDChgCellRecord(type, data)); break;
						case 0x013D: r = (Record*)(new RRTabIdRecord(type, data)); break;
						case 0x013E: r = (Record*)(new RRDRenSheetRecord(type, data)); break;
						case 0x013F: r = (Record*)(new RRSortRecord(type, data)); break;
						case 0x0140: r = (Record*)(new RRDMoveRecord(type, data)); break;
						case 0x014A: r = (Record*)(new RRFormatRecord(type, data)); break;
						case 0x014B: r = (Record*)(new RRAutoFmtRecord(type, data)); break;
						case 0x014D: r = (Record*)(new RRInsertShRecord(type, data)); break;
						case 0x014E: r = (Record*)(new RRDMoveBeginRecord(type, data)); break;
						case 0x014F: r = (Record*)(new RRDMoveEndRecord(type, data)); break;
						case 0x0150: r = (Record*)(new RRDInsDelBeginRecord(type, data)); break;
						case 0x0151: r = (Record*)(new RRDInsDelEndRecord(type, data)); break;
						case 0x0152: r = (Record*)(new RRDConflictRecord(type, data)); break;
						case 0x0153: r = (Record*)(new RRDDefNameRecord(type, data)); break;
						case 0x0154: r = (Record*)(new RRDRstEtxpRecord(type, data)); break;
						case 0x015F: r = (Record*)(new LRngRecord(type, data)); break;
						case 0x0160: r = (Record*)(new UsesELFsRecord(type, data)); break;
						case 0x0161: r = (Record*)(new DSFRecord(type, data)); break;
						case 0x0191: r = (Record*)(new CUsrRecord(type, data)); break;
						case 0x0192: r = (Record*)(new CbUsrRecord(type, data)); break;
						case 0x0193: r = (Record*)(new UsrInfoRecord(type, data)); break;
						case 0x0194: r = (Record*)(new UsrExclRecord(type, data)); break;
						case 0x0195: r = (Record*)(new FileLockRecord(type, data)); break;
						case 0x0196: r = (Record*)(new RRDInfoRecord(type, data)); break;
						case 0x0197: r = (Record*)(new BCUsrsRecord(type, data)); break;
						case 0x0198: r = (Record*)(new UsrChkRecord(type, data)); break;
						case 0x01A9: r = (Record*)(new UserBViewRecord(type, data)); break;
						case 0x01AA: {
							//?? One or the other??
							r = (Record*)(new UserSViewBegin_ChartRecord(type, data)); break;
							//r = (Record*)(new UserSViewBeginRecord(type, data)); break;
						}
						case 0x01AB: r = (Record*)(new UserSViewEndRecord(type, data)); break;
						case 0x01AC: r = (Record*)(new RRDUserViewRecord(type, data)); break;
						case 0x01AD: r = (Record*)(new QsiRecord(type, data)); break;
						case 0x01AE: r = (Record*)(new SupBookRecord(type, data)); break;
						case 0x01AF: r = (Record*)(new Prot4RevRecord(type, data)); break;
						case 0x01B0: r = (Record*)(new CondFmtRecord(type, data)); break;
						case 0x01B1: r = (Record*)(new CFRecord(type, data)); break;
						case 0x01B2: r = (Record*)(new DValRecord(type, data)); break;
						case 0x01B5: r = (Record*)(new DconBinRecord(type, data)); break;
						case 0x01B6: r = (Record*)(new TxORecord(type, data)); break;
						case 0x01B7: r = (Record*)(new RefreshAllRecord(type, data)); break;
						case 0x01B8: r = (Record*)(new HLinkRecord(type, data)); break;
						case 0x01B9: r = (Record*)(new LelRecord(type, data)); break;
						case 0x01BA: r = (Record*)(new CodeNameRecord(type, data)); break;
						case 0x01BB: r = (Record*)(new SXFDBTypeRecord(type, data)); break;
						case 0x01BC: r = (Record*)(new Prot4RevPassRecord(type, data)); break;
						case 0x01BD: r = (Record*)(new ObNoMacrosRecord(type, data)); break;
						case 0x01BE: r = (Record*)(new DvRecord(type, data)); break;
						case 0x01C0: r = (Record*)(new Excel9FileRecord(type, data)); break;
						case 0x01C1: r = (Record*)(new RecalcIdRecord(type, data)); break;
						case 0x01C2: r = (Record*)(new EntExU2Record(type, data)); break;
						case 0x0200: r = (Record*)(new DimensionsRecord(type, data)); break;
						case 0x0201: r = (Record*)(new BlankRecord(type, data)); break;
						case 0x0203: r = (Record*)(new NumberRecord(type, data)); break;
						case 0x0204: r = (Record*)(new LabelRecord(type, data)); break;
						case 0x0205: r = (Record*)(new BoolErrRecord(type, data)); break;
						case 0x0207: r = (Record*)(new StringRecord(type, data)); break;
						case 0x0208: r = (Record*)(new RowRecord(type, data)); break;
						case 0x020B: r = (Record*)(new IndexRecord(type, data)); break;
						case 0x0221: r = (Record*)(new ArrayRecord(type, data)); break;
						case 0x0225: r = (Record*)(new DefaultRowHeightRecord(type, data)); break;
						case 0x0236: r = (Record*)(new TableRecord(type, data)); break;
						case 0x023E: r = (Record*)(new Window2Record(type, data)); break;
						case 0x027E: r = (Record*)(new RKRecord(type, data)); break;
						case 0x0293: r = (Record*)(new StyleRecord(type, data)); break;
						case 0x0418: r = (Record*)(new BigNameRecord(type, data)); break;
						case 0x041E: r = (Record*)(new FormatRecord(type, data)); break;
						case 0x043C: r = (Record*)(new ContinueBigNameRecord(parser, type, data)); break;
						case 0x04BC: r = (Record*)(new ShrFmlaRecord(type, data)); break;
						case 0x0800: r = (Record*)(new HLinkTooltipRecord(type, data)); break;
						case 0x0801: r = (Record*)(new WebPubRecord(type, data)); break;
						case 0x0802: r = (Record*)(new QsiSXTagRecord(type, data)); break;
						case 0x0803: r = (Record*)(new DBQueryExtRecord(type, data)); break;
						case 0x0804: r = (Record*)(new ExtStringRecord(type, data)); break;
						case 0x0805: r = (Record*)(new TxtQryRecord(type, data)); break;
						case 0x0806: r = (Record*)(new QsirRecord(type, data)); break;
						case 0x0807: r = (Record*)(new QsifRecord(type, data)); break;
						case 0x0808: r = (Record*)(new RRDTQSIFRecord(type, data)); break;
						case 0x0809: r = (Record*)(new BOFRecord(type, data)); break;
						case 0x080A: r = (Record*)(new OleDbConnRecord(type, data)); break;
						case 0x080B: r = (Record*)(new WOptRecord(type, data)); break;
						case 0x080C: r = (Record*)(new SXViewExRecord(type, data)); break;
						case 0x080D: r = (Record*)(new SXTHRecord(type, data)); break;
						case 0x080E: r = (Record*)(new SXPIExRecord(type, data)); break;
						case 0x080F: r = (Record*)(new SXVDTExRecord(type, data)); break;
						case 0x0810: r = (Record*)(new SXViewEx9Record(type, data)); break;
						case 0x0812: r = (Record*)(new ContinueFrtRecord(parser, type, data)); break;
						case 0x0813: r = (Record*)(new RealTimeDataRecord(type, data)); break;
						case 0x0850: r = (Record*)(new ChartFrtInfoRecord(type, data)); break;
						case 0x0851: r = (Record*)(new FrtWrapperRecord(type, data)); break;
						case 0x0852: r = (Record*)(new StartBlockRecord(type, data)); break;
						case 0x0853: r = (Record*)(new EndBlockRecord(type, data)); break;
						case 0x0854: r = (Record*)(new StartObjectRecord(type, data)); break;
						case 0x0855: r = (Record*)(new EndObjectRecord(type, data)); break;
						case 0x0856: r = (Record*)(new CatLabRecord(type, data)); break;
						case 0x0857: r = (Record*)(new YMultRecord(type, data)); break;
						case 0x0858: r = (Record*)(new SXViewLinkRecord(type, data)); break;
						case 0x0859: r = (Record*)(new PivotChartBitsRecord(type, data)); break;
						case 0x085A: r = (Record*)(new FrtFontListRecord(type, data)); break;
						case 0x0862: r = (Record*)(new SheetExtRecord(type, data)); break;
						case 0x0863: r = (Record*)(new BookExtRecord(type, data)); break;
						case 0x0864: r = (Record*)(new SXAddlRecord(type, data)); break;
						case 0x0865: r = (Record*)(new CrErrRecord(type, data)); break;
						case 0x0866: r = (Record*)(new HFPictureRecord(type, data)); break;
						case 0x0867: r = (Record*)(new FeatHdrRecord(type, data)); break;
						case 0x0868: r = (Record*)(new FeatRecord(type, data)); break;
						case 0x086A: r = (Record*)(new DataLabExtRecord(type, data)); break;
						case 0x086B: r = (Record*)(new DataLabExtContentsRecord(type, data)); break;
						case 0x086C: r = (Record*)(new CellWatchRecord(type, data)); break;
						case 0x0871: r = (Record*)(new FeatHdr11Record(type, data)); break;
						case 0x0872: r = (Record*)(new Feature11Record(type, data)); break;
						case 0x0874: r = (Record*)(new DropDownObjIdsRecord(type, data)); break;
						case 0x0875: r = (Record*)(new ContinueFrt11Record(parser, type, data)); break;
						case 0x0876: r = (Record*)(new DConnRecord(type, data)); break;
						case 0x0877: r = (Record*)(new List12Record(type, data)); break;
						case 0x0878: r = (Record*)(new Feature12Record(type, data)); break;
						case 0x0879: r = (Record*)(new CondFmt12Record(type, data)); break;
						case 0x087A: r = (Record*)(new CF12Record(type, data)); break;
						case 0x087B: r = (Record*)(new CFExRecord(type, data)); break;
						case 0x087C: r = (Record*)(new XFCRCRecord(type, data)); break;
						case 0x087D: r = (Record*)(new XFExtRecord(type, data)); break;
						case 0x087E: r = (Record*)(new AutoFilter12Record(type, data)); break;
						case 0x087F: r = (Record*)(new ContinueFrt12Record(parser, type, data)); break;
						case 0x0884: r = (Record*)(new MDTInfoRecord(type, data)); break;
						case 0x0885: r = (Record*)(new MDXStrRecord(type, data)); break;
						case 0x0886: r = (Record*)(new MDXTupleRecord(type, data)); break;
						case 0x0887: r = (Record*)(new MDXSetRecord(type, data)); break;
						case 0x0888: r = (Record*)(new MDXPropRecord(type, data)); break;
						case 0x0889: r = (Record*)(new MDXKPIRecord(type, data)); break;
						case 0x088A: r = (Record*)(new MDBRecord(type, data)); break;
						case 0x088B: r = (Record*)(new PLVRecord(type, data)); break;
						case 0x088C: r = (Record*)(new Compat12Record(type, data)); break;
						case 0x088D: r = (Record*)(new DXFRecord(type, data)); break;
						case 0x088E: r = (Record*)(new TableStylesRecord(type, data)); break;
						case 0x088F: r = (Record*)(new TableStyleRecord(type, data)); break;
						case 0x0890: r = (Record*)(new TableStyleElementRecord(type, data)); break;
						case 0x0892: r = (Record*)(new StyleExtRecord(type, data)); break;
						case 0x0893: r = (Record*)(new NamePublishRecord(type, data)); break;
						case 0x0894: r = (Record*)(new NameCmtRecord(type, data)); break;
						case 0x0895: r = (Record*)(new SortDataRecord(type, data)); break;
						case 0x0896: r = (Record*)(new ThemeRecord(type, data)); break;
						case 0x0897: r = (Record*)(new GUIDTypeLibRecord(type, data)); break;
						case 0x0898: r = (Record*)(new FnGrp12Record(type, data)); break;
						case 0x0899: r = (Record*)(new NameFnGrp12Record(type, data)); break;
						case 0x089A: r = (Record*)(new MTRSettingsRecord(type, data)); break;
						case 0x089B: r = (Record*)(new CompressPicturesRecord(type, data)); break;
						case 0x089C: r = (Record*)(new HeaderFooterRecord(type, data)); break;
						case 0x089D: r = (Record*)(new CrtLayout12Record(type, data)); break;
						case 0x089E: r = (Record*)(new CrtMlFrtRecord(type, data)); break;
						case 0x089F: r = (Record*)(new CrtMlFrtContinueRecord(parser, type, data)); break;
						case 0x08A3: r = (Record*)(new ForceFullCalculationRecord(type, data)); break;
						case 0x08A4: r = (Record*)(new ShapePropsStreamRecord(type, data)); break;
						case 0x08A5: r = (Record*)(new TextPropsStreamRecord(type, data)); break;
						case 0x08A6: r = (Record*)(new RichTextStreamRecord(type, data)); break;
						case 0x08A7: r = (Record*)(new CrtLayout12ARecord(type, data)); break;
						case 0x1001: r = (Record*)(new UnitsRecord(type, data)); break;
						case 0x1002: r = (Record*)(new ChartRecord(type, data)); break;
						case 0x1003: r = (Record*)(new SeriesRecord(type, data)); break;
						case 0x1006: r = (Record*)(new DataFormatRecord(type, data)); break;
						case 0x1007: r = (Record*)(new LineFormatRecord(type, data)); break;
						case 0x1009: r = (Record*)(new MarkerFormatRecord(type, data)); break;
						case 0x100A: r = (Record*)(new AreaFormatRecord(type, data)); break;
						case 0x100B: r = (Record*)(new PieFormatRecord(type, data)); break;
						case 0x100C: r = (Record*)(new AttachedLabelRecord(type, data)); break;
						case 0x100D: r = (Record*)(new SeriesTextRecord(type, data)); break;
						case 0x1014: r = (Record*)(new ChartFormatRecord(type, data)); break;
						case 0x1015: r = (Record*)(new LegendRecord(type, data)); break;
						case 0x1016: r = (Record*)(new SeriesListRecord(type, data)); break;
						case 0x1017: r = (Record*)(new BarRecord(type, data)); break;
						case 0x1018: r = (Record*)(new LineRecord(type, data)); break;
						case 0x1019: r = (Record*)(new PieRecord(type, data)); break;
						case 0x101A: r = (Record*)(new AreaRecord(type, data)); break;
						case 0x101B: r = (Record*)(new ScatterRecord(type, data)); break;
						case 0x101C: r = (Record*)(new CrtLineRecord(type, data)); break;
						case 0x101D: r = (Record*)(new AxisRecord(type, data)); break;
						case 0x101E: r = (Record*)(new TickRecord(type, data)); break;
						case 0x101F: r = (Record*)(new ValueRangeRecord(type, data)); break;
						case 0x1020: r = (Record*)(new CatSerRangeRecord(type, data)); break;
						case 0x1021: r = (Record*)(new AxisLineRecord(type, data)); break;
						case 0x1022: r = (Record*)(new CrtLinkRecord(type, data)); break;
						case 0x1024: r = (Record*)(new DefaultTextRecord(type, data)); break;
						case 0x1025: r = (Record*)(new TextRecord(type, data)); break;
						case 0x1026: r = (Record*)(new FontXRecord(type, data)); break;
						case 0x1027: r = (Record*)(new ObjectLinkRecord(type, data)); break;
						case 0x1032: r = (Record*)(new FrameRecord(type, data)); break;
						case 0x1033: r = (Record*)(new BeginRecord(type, data)); break;
						case 0x1034: r = (Record*)(new EndRecord(type, data)); break;
						case 0x1035: r = (Record*)(new PlotAreaRecord(type, data)); break;
						case 0x103A: r = (Record*)(new Chart3dRecord(type, data)); break;
						case 0x103C: r = (Record*)(new PicFRecord(type, data)); break;
						case 0x103D: r = (Record*)(new DropBarRecord(type, data)); break;
						case 0x103E: r = (Record*)(new RadarRecord(type, data)); break;
						case 0x103F: r = (Record*)(new SurfRecord(type, data)); break;
						case 0x1040: r = (Record*)(new RadarAreaRecord(type, data)); break;
						case 0x1041: r = (Record*)(new AxisParentRecord(type, data)); break;
						case 0x1043: r = (Record*)(new LegendExceptionRecord(type, data)); break;
						case 0x1044: r = (Record*)(new ShtPropsRecord(type, data)); break;
						case 0x1045: r = (Record*)(new SerToCrtRecord(type, data)); break;
						case 0x1046: r = (Record*)(new AxesUsedRecord(type, data)); break;
						case 0x1048: r = (Record*)(new SBaseRefRecord(type, data)); break;
						case 0x104A: r = (Record*)(new SerParentRecord(type, data)); break;
						case 0x104B: r = (Record*)(new SerAuxTrendRecord(type, data)); break;
						case 0x104E: r = (Record*)(new IFmtRecordRecord(type, data)); break;
						case 0x104F: r = (Record*)(new PosRecord(type, data)); break;
						case 0x1050: r = (Record*)(new AlRunsRecord(type, data)); break;
						case 0x1051: r = (Record*)(new BRAIRecord(type, data)); break;
						case 0x105B: r = (Record*)(new SerAuxErrBarRecord(type, data)); break;
						case 0x105C: r = (Record*)(new ClrtClientRecord(type, data)); break;
						case 0x105D: r = (Record*)(new SerFmtRecord(type, data)); break;
						case 0x105F: r = (Record*)(new Chart3DBarShapeRecord(type, data)); break;
						case 0x1060: r = (Record*)(new FbiRecord(type, data)); break;
						case 0x1061: r = (Record*)(new BopPopRecord(type, data)); break;
						case 0x1062: r = (Record*)(new AxcExtRecord(type, data)); break;
						case 0x1063: r = (Record*)(new DatRecord(type, data)); break;
						case 0x1064: r = (Record*)(new PlotGrowthRecord(type, data)); break;
						case 0x1065: r = (Record*)(new SIIndexRecord(type, data)); break;
						case 0x1066: r = (Record*)(new GelFrameRecord(type, data)); break;
						case 0x1067: r = (Record*)(new BopPopCustomRecord(type, data)); break;
						case 0x1068: r = (Record*)(new Fbi2Record(type, data)); break;
						default: r = new Record(type, data);
						}
						break;
					}
					case 1280: { // BIFF5
						switch (type) {
						case 0x0809: r = (Record*)(new BOFRecord(type, data)); break;
						case 0x000A: r = (Record*)(new EOFRecord(type, data)); break;
						case 0x0085: {
							r = (Record*)(new BoundSheet5Record(type, data));
							break;
						}
						default: r = new Record(type, data);
						}
						break;
					}
					case 1024: { //BIFF4
						switch (type)
						{
						case 0x0409: r = (Record*)(new BOFRecord(type, data)); break;
						default: r = new Record(type, data); break;
						}
						break;
					}
					case 768: { //BIFF3
						switch (type)
						{
						case 0x0209: r = (Record*)(new BOFRecord(type, data)); break;
						default: r = new Record(type, data); break;
						}
						break;
					}
					case 512: { //BIFF2
						switch (type) {
						case 0x0009: r = (Record*)(new BOFRecord(type, data)); break;
						default: r = new Record(type, data); break;
						}
						break;
					}
					default: { //case of first record...we don't know the version...try all possible BOF version, or generic
						switch (type) {
						case 0x0009:
						case 0x0209:
						case 0x0409:
						case 0x0809:
							r = (Record*)(new BOFRecord(type, data)); 
							break;
						default: r = new Record(type, data);
						}
						break;
					}
					}
				}
				catch (const std::range_error) {

#ifdef DEBUG
					std::cerr << "Error Parsing Record: [0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << type;
					std::cerr << "=" << GetRecordTypeStr(type) << "]" << std::endl;
#endif
					//there was an error parsing a record...ignore and move on
				}
				return r;
			}

		}
	}
}