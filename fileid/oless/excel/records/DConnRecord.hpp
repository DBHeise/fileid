#pragma once

#include "Record.hpp"

namespace OleStructuredStorage {
	namespace Excel {
		namespace Records {
			namespace DConn {

				class Connection : public common::IExportable {
				public:
					unsigned int bytesRead = 0;
					virtual std::string ToCsv() const { return ""; }
					virtual std::string ToText() const { return ""; }
				};
				class ConnectionString : Connection {
				private:
					std::string connstr;
				public:
					static ConnectionString* Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
						ConnectionString* ans = new ConnectionString();
						auto tmp = XLUnicodeStringSegmented::Read(buffer, offset, max);
						ans->bytesRead = tmp.bytesRead;
						ans->connstr = tmp.ToOneString();
						return ans;
					}
					virtual std::string ToXml() const { 
						std::ostringstream str;
						str << "<Connection>";
						str << "<ConnString><![CDATA[" << this->connstr << "]]> </ConnString>";
						str << "</Connection>";
						return str.str();
					}
					virtual std::string ToJson() const {
						std::ostringstream str;
						str << "{\"ConnectionString\":\"" << common::JsonEscape(this->connstr) << "\"}";
						return str.str();
					}
				};
				class ConnectionWeb : Connection {
				private:
					std::string url;
					std::string method;
				public:
					static ConnectionWeb* Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
						ConnectionWeb* ans = new ConnectionWeb();
						unsigned int index = offset;

						auto tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
						ans->bytesRead = tmp.bytesRead;
						index += tmp.bytesRead;
						ans->url = tmp.ToOneString();

						tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
						ans->bytesRead += tmp.bytesRead;
						index += tmp.bytesRead;
						ans->method = tmp.ToOneString();

						return ans;
					}
					virtual std::string ToXml() const {
						std::ostringstream str;
						str << "<Connection>";
						str << "<Url><![CDATA[" << this->url << "]]></Url>";
						str << "<WebPost>" << this->method << "]]></WebPost>";
						str << "</Connection>";
						return str.str();
					}
					virtual std::string ToJson() const {
						std::ostringstream str;
						str << "{";
						str << "\"Url\":\"" << this->url << "\",";
						str << "\"WebPost\":\"" << this->method << "\"";
						str << "}";
						return str.str();
					}
				};
				class ConnectionOleDb : Connection {
				private:
					unsigned int nDrillthroughRows;
					unsigned short cOleDb;
					std::vector<unsigned short> rglOleDbValid;
					std::vector<std::string> rgConn;
				public:
					static ConnectionOleDb* Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
						ConnectionOleDb* ans = new ConnectionOleDb();
						unsigned int index = offset;

						ans->nDrillthroughRows = common::ReadUInt(buffer, max, index);
						index += 4;

						ans->cOleDb = common::ReadUShort(buffer, max, index);
						index += 2;

						ans->rglOleDbValid.resize(ans->cOleDb);
						for (int i = 0; i < ans->cOleDb; i++)
						{
							ans->rglOleDbValid.push_back(common::ReadUShort(buffer, max, index));
							index += 2;
						}

						index += 2 * (4 - ans->cOleDb); //rglOleDbInvalid
						index += 2;                    //unused

						for (int i = 0; i < ans->cOleDb; i++)
						{
							auto tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
							index += tmp.bytesRead;
							ans->rgConn.push_back(tmp.ToOneString());
						}

						ans->bytesRead = index - offset;
						return ans;
					}
					virtual std::string ToXml() const {
						std::ostringstream str;		
						str << "<Connection>";
						str << "<nDrillthroughRows>"<< this->nDrillthroughRows << "</nDrillthroughRows>";
						str << "<cOleDb>" << this->cOleDb << "</cOleDb>";
						str << "<Strings>";
						for (int i = 0; i < this->cOleDb; i++)
						{
							str << "<ConnStr>";
							str << "<Type>" << this->rglOleDbValid[i] << "</Type>";
							str << "<Conn>" << common::JsonEscape(this->rgConn[i]) << "</Conn>";
							str << "</ConnStr>";
						}
						str << "</Strings>";
						str << "</Connection>";
						return str.str();
					}
					virtual std::string ToJson() const {
						std::ostringstream str;
						str << "{";
						str << "\"nDrillthroughRows\":" << this->nDrillthroughRows << ",";
						str << "\"cOleDb\":" << this->cOleDb << ",";
						str << "\"Strings\":[";
						for (int i = 0; i < this->cOleDb; i++)
						{
							str << "{";
							str << "\"Type\":" << this->rglOleDbValid[i] << ",";
							str << "\"Conn\":\"" << common::JsonEscape(this->rgConn[i]) << "\"";
							str << "}";
						}
						str << "]";
						str << "}";
						return str.str();
					}
				};
				class ConnectionTxtQry : Connection {
				public:
					static ConnectionTxtQry* Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max) {
						throw std::exception("Not Implemented!");
					}
					virtual std::string ToXml() const {
						throw std::exception("Not Implemented!");
					}
					virtual std::string ToJson() const {
						throw std::exception("Not Implemented!");
					}
				};

				struct DConnParameterMiddle {
					unsigned short pbt : 3;
					unsigned short reserved : 13;
					unsigned short wTypeSql;
					unsigned short fDefaultName : 1;
					unsigned short unused : 15;
				};

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/8bcedc27-0064-4f81-87f8-6b74f67342da
				// The DConnParameter structure specifies a parameter of a parameterized query.
				class DConnParameter : public common::IExportable {
				private:
					std::string name;
					DConnParameterMiddle* chunk;

				public:
					unsigned int bytesRead = 0;
					static DConnParameter Read(const unsigned char* buffer, const unsigned int offset, const unsigned int max)
					{
						DConnParameter ans;
						unsigned int index = offset;

						auto tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
						index += tmp.bytesRead;
						ans.name = tmp.ToOneString();

						//ans.chunk = reinterpret_cast<DConnParameterMiddle*>(buffer + index);
						throw std::exception("Not Implemented!");
						return ans;
					}
					virtual std::string ToJson() const {
						throw std::exception("Not Implemented!");
					};
					virtual std::string ToXml() const {
						throw std::exception("Not Implemented!");
					}
					virtual std::string ToCsv() const { return ""; }
					virtual std::string ToText() const { return ""; }
				};

				struct ConnGrbitDbt {};

				// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/edd38099-e87b-4db6-b6e2-8e7c4bef8124
				// The ConnGrbitDbtWeb structure specifies the query flags for a Web data connection.
				struct ConnGrbitDbtWeb : ConnGrbitDbt {
					unsigned short fParsePreFormatted : 1;
					unsigned short fConsecDelim : 1;
					unsigned short fSameSettings : 1;
					unsigned short fXL97Format : 1;
					unsigned short fNoDateRecog : 1;
					unsigned short fRefreshedInXl9 : 1;
					unsigned short reserved : 10;
				};

				// from:https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/b6e55e12-4901-4c8f-827e-3110cfee247c
				// The ConnGrbitDbtOledb structure specifies the external connection properties for an OLE DB data connection.
				struct ConnGrbitDbtOledb : ConnGrbitDbt {
					unsigned short dbost : 3;
					unsigned short fLocalConn : 1;
					unsigned short fNoRefreshCube : 1;
					unsigned short fUseOfficeLcid : 1;
					unsigned short fSrvFmtNum : 1;
					unsigned short fSrvFmtBack : 1;
					unsigned short fSrvFmtFore : 1;
					unsigned short fSrvFmtFlags : 1;
					unsigned short fSupportsLangCellProp : 1;
					unsigned short fSrvSupportsClientCube : 1;
					unsigned short reserved : 4;
				};

				// from:https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/ccb9eb2c-0b03-446a-88dd-6b21ce748aa8
				// The ConnGrbitDbtAdo structure specifies the query flags for an ADO data connection.
				struct ConnGrbitDbtAdo : ConnGrbitDbt {
					unsigned short reserved1 : 8;
					unsigned short fAdoRefreshable : 1;
					unsigned short reserved2 : 7;
				};

				struct DConnHeader {
					unsigned int frtheaderOld;
					unsigned short dbt;

					unsigned char fSavePwd : 1;
					unsigned char fTablesOnlyHtml : 1;
					unsigned char fTableNames : 1;
					unsigned char fDeleted : 1;
					unsigned char fStandAlone : 1;
					unsigned char fAlwaysUseConnectionFile : 1;
					unsigned char fBackgroundQuery : 1;
					unsigned char fRefreshOnLoad : 1;
					unsigned char fSaveData : 1;
					unsigned char unused1 : 7;

					unsigned short cParams;
					unsigned short reserved1;

					unsigned char fMaintain : 1;
					unsigned char fNewQuery : 1;
					unsigned char fImportXmlSource : 1;
					unsigned char fSPListSrc : 1;
					unsigned char fSPListReinitCache : 1;
					unsigned char unused2 : 2;
					unsigned char fSrcIsXml : 1;

					unsigned short reserved2;

					unsigned short grbitDbt;

					unsigned char bVerDbqueryEdit;
					unsigned char bVerDbqueryRefreshed;
					unsigned char bVerDbqueryRefreshableMin;
					unsigned short wRefreshInterval;
					unsigned short wHtmlFmt;

					unsigned int rcc;

					unsigned char credMethod;
					unsigned char reserved3;
				};

				std::string dbtToString(unsigned short dbt) {
					std::ostringstream str;
					if (dbt == 0x1) {
						str << "ODBC";
					}
					else if (dbt == 0x2) {
						str << "DAO";
					}
					else if (dbt == 0x4) {
						str << "WEB";
					}
					else if (dbt == 0x5) {
						str << "OLEDB";
					}
					else if (dbt == 0x6) {
						str << "TXT";
					}
					else if (dbt == 0x7) {
						str << "ADO";
					}
					else {
						str << "UNKNOWN (" << dbt << ")";
					}
					return str.str();
				}
			}

			// from: https://docs.microsoft.com/en-us/openspecs/office_file_formats/ms-xls/a2ace8d3-0194-4570-9bc5-a865e0d78a21
			// The DConn record specifies information for a single data connection.			
			class DConnRecord : public Record {
				DConn::DConnHeader* header;
				std::string rgchSourceDataFile;
				std::string rgchSourceConnectionFile;
				std::string rgchConnectionName;
				std::string rgchConnectionDesc;
				std::string rgchSSOApplicationID;
				std::string tableNames;
				std::vector<DConn::DConnParameter*> params;
				DConn::Connection* connection;
				std::string rgbSQL;
				std::string rgbSQLSav;
				std::string rgbEditWebPage;
				//DConnId* id;

			public:
				DConnRecord(unsigned short type, std::vector<uint8_t> data) : Record(type, data) 
				{
					//unsigned int index = 0;
					//auto buffer = this->Data.data();
					//auto max = this->Data.size();

					//this->header = reinterpret_cast<DConn::DConnHeader*>(buffer);
					//index += 29;
					//
					//auto tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//index += tmp.bytesRead;
					//this->rgchSourceDataFile = tmp.ToOneString();

					//tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//index += tmp.bytesRead;
					//this->rgchSourceConnectionFile = tmp.ToOneString();;

					//tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//index += tmp.bytesRead;
					//this->rgchConnectionName = tmp.ToOneString();;

					//tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//index += tmp.bytesRead;
					//this->rgchConnectionDesc = tmp.ToOneString();

					//tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//index += tmp.bytesRead;
					//this->rgchSSOApplicationID = tmp.ToOneString();

					//if (this->header->fTableNames == 1) {
					//	tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//	index += tmp.bytesRead;
					//	this->tableNames = tmp.ToOneString();
					//}

					//if (this->header->fStandAlone == 1) {
					//	//params
					//	this->params.resize(this->header->cParams);
					//	for (int i = 0; i < this->header->cParams; i++)
					//	{
					//		auto p = DConn::DConnParameter::Read(buffer, index, max);
					//		index += p.bytesRead;
					//		this->params.push_back(&p);
					//	}
					//}

					//switch (this->header->dbt)
					//{
					//case 0x1:
					//	this->connection = (DConn::Connection*)DConn::ConnectionString::Read(buffer, index, max);
					//	break;
					//case 0x4:
					//	this->connection = (DConn::Connection*)DConn::ConnectionWeb::Read(buffer, index, max);
					//	break;
					//case 0x5:
					//	this->connection = (DConn::Connection*)DConn::ConnectionOleDb::Read(buffer, index, max);
					//	break;
					//case 0x6:
					//	this->connection = (DConn::Connection*)DConn::ConnectionTxtQry::Read(buffer, index, max);
					//	break;
					//default:
					//	this->connection = nullptr;
					//	break;
					//}
					//if (this->connection != nullptr) {
					//	index += this->connection->bytesRead;
					//}

					//if (index < max) {
					//	tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//	index += tmp.bytesRead;
					//	this->rgbSQL = tmp.ToOneString();
					//}
					//if (index < max) {
					//	tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//	index += tmp.bytesRead;
					//	this->rgbSQLSav = tmp.ToOneString();
					//}
					//if (index < max) {
					//	tmp = XLUnicodeStringSegmented::Read(buffer, index, max);
					//	index += tmp.bytesRead;
					//	this->rgbEditWebPage = tmp.ToOneString();
					//}

					////id
				}

				//std::string ToXml() const override
				//{
				//	std::ostringstream str;
				//	str << "<Record>";
				//	str << "<Type>" << GetRecordTypeStr(this->Type) << "</Type>";
				//	str << "<Length>" << this->Length << "</Length>";
				//	
				//	str << "<frtHeaderOld>" << this->header->frtheaderOld << "</frtHeaderOld>";
				//	str << "<DataSourceType>" << DConn::dbtToString(this->header->dbt) << "</DataSourceType>";
				//	str << "<fSavePassword>" << this->header->fSavePwd << "</SavePassword>";
				//	str << "<fTablesOnlyHtml>" << this->header->fTablesOnlyHtml << "</TablesOnlyHtml>";
				//	str << "<fTableNames>" << this->header->fTableNames << "</TableNames>";
				//	str << "<fDeleted>" << this->header->fDeleted << "</fDeleted>";
				//	str << "<fStandAlone>" << this->header->fStandAlone << "</fStandAlone>";
				//	str << "<fAlwaysUseConnectionFile>" << this->header->fAlwaysUseConnectionFile << "</fAlwaysUseConnectionFile>";
				//	str << "<fBackgroundQuery>" << this->header->fBackgroundQuery << "</fBackgroundQuery>";
				//	str << "<fRefreshOnLoad>" << this->header->fRefreshOnLoad << "</fRefreshOnLoad>";
				//	str << "<fSaveData>" << this->header->fSaveData << "</fSaveData>";
				//	str << "<unused1>" << this->header->unused1 << "</unused1>";
				//	str << "<cParams>" << this->header->cParams << "</cParams>";
				//	str << "<reserved1>" << this->header->reserved1 << "</reserved1>";
				//	str << "<fMaintain>" << this->header->fMaintain << "</fMaintain>";
				//	str << "<fNewQuery>" << this->header->fNewQuery << "</fNewQuery>";
				//	str << "<fImportXmlSource>" << this->header->fImportXmlSource << "</fImportXmlSource>";
				//	str << "<fSPListSrc>" << this->header->fSPListSrc << "</fSPListSrc>";
				//	str << "<fSPListReinitCache>" << this->header->fSPListReinitCache << "</fSPListReinitCache>";
				//	str << "<unused2>" << this->header->unused2 << "</unused2>";
				//	str << "<fSrcIsXml>" << this->header->fSrcIsXml << "</fSrcIsXml>";
				//	str << "<reserved2>" << this->header->reserved2 << "</reserved2>";
				//	str << "<grbitDbt>" << this->header->grbitDbt << "</grbitDbt>";
				//	str << "<bVerDbqueryEdit>" << this->header->bVerDbqueryEdit << "</bVerDbqueryEdit>";
				//	str << "<bVerDbqueryRefreshed>" << this->header->bVerDbqueryRefreshed << "</bVerDbqueryRefreshed>";
				//	str << "<bVerDbqueryRefreshableMin>" << this->header->bVerDbqueryRefreshableMin << "</bVerDbqueryRefreshableMin>";
				//	str << "<wRefreshInterval>" << this->header->wRefreshInterval << "</wRefreshInterval>";
				//	str << "<wHtmlFmt>" << this->header->wHtmlFmt << "</wHtmlFmt>";
				//	str << "<rcc>" << this->header->rcc << "</rcc>";
				//	str << "<credMethod>" << this->header->credMethod << "</credMethod>";
				//	str << "<reserved3>" << this->header->reserved3 << "</reserved3>";

				//	str << "<SourceDataFile>" << this->rgchSourceDataFile << "</SourceDataFile>";
				//	str << "<ConnectionName>" << this->rgchConnectionName << "</ConnectionName>";
				//	str << "<ConnectionDesc>" << this->rgchConnectionDesc << "</ConnectionDesc>";
				//	str << "<SSOApplicationID>" << this->rgchSSOApplicationID << "</SSOApplicationID>";
				//	str << "<TableNames>" << this->tableNames << "</TableNames>";
				//	
				//	str << "<params>";
				//	for (auto p: this->params) {
				//		str << p->ToXml();
				//	}
				//	str << "</params>";

				//	if (this->connection != nullptr) {
				//		switch (this->header->dbt)
				//		{
				//		case 0x1:
				//			str << ((DConn::ConnectionString*)this->connection)->ToXml();
				//			break;
				//		case 0x4:
				//			str << ((DConn::ConnectionWeb*)this->connection)->ToXml();
				//			break;
				//		case 0x5:
				//			str << ((DConn::ConnectionOleDb*)this->connection)->ToXml();
				//			break;
				//		case 0x6:
				//			str << ((DConn::ConnectionTxtQry*)this->connection)->ToXml();
				//			break;
				//		}
				//	}

				//	str << "<SQL>" << this->rgbSQL << "</SQL>";
				//	str << "<SQLSav>" << this->rgbSQLSav << "</SQLSav>";
				//	str << "<EditWebPage>" << this->rgbEditWebPage << "</EditWebPage>";
				//	// str << "<DConnId>" << this->id << "</DConnId>";

				//	str << "</Record>";
				//	return str.str();
				//}
				//std::string ToJson() const override
				//{
				//	std::ostringstream str;
				//	str << "{";
				//	str << "\"Type\":\"" << GetRecordTypeStr(this->Type) << "\",";
				//	str << "\"Length\":" << this->Length << ",";

				//	str << "\"frtHeaderOld\":" << this->header->frtheaderOld << ",";
				//	str << "\"dbt\":\"" << DConn::dbtToString(this->header->dbt) << "\"";

				//	str << "}";
				//	return str.str();
				//}
			};
		}
	}
}
