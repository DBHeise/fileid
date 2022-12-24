# FileId

Generic file identifier (for linux and windows)

[![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg) [![Windows](https://svgshare.com/i/ZhY.svg)](https://svgshare.com/i/ZhY.svg) [![License](https://badgen.net/github/license/DBHeise/fileid)](https://github.com/DBHeise/fileid/blob/master/LICENSE)

[![last-tag](https://badgen.net/github/tag/DBHeise/fileid)]() [![last-commit](https://badgen.net/github/last-commit/DBHeise/fileid)]()

[![Stars](https://badgen.net/github/stars/DBHeise/fileid)](https://github.com/DBHeise/fileid/stargazers)
[![Open-Issues](https://badgen.net/github/open-issues/DBHeise/fileid)](https://github.com/DBHeise/fileid/issues?q=is%3Aopen+is%3Aissue)
[![Commits](https://badgen.net/github/commits/DBHeise/fileid)](https://github.com/DBHeise/fileid/commits) ![GitHub all releases](https://img.shields.io/github/downloads/DBHeise/fileid/total) [![GitHub watchers](https://badgen.net/github/watchers/DBHeise/fileid/)](https://GitHub.com/DBHeise/fileid/watchers/)

[![Build & Push](https://github.com/DBHeise/fileid/actions/workflows/build.yml/badge.svg)](https://github.com/DBHeise/fileid/actions/workflows/build.yml)[![Analysis](https://github.com/DBHeise/fileid/actions/workflows/analysis.yml/badge.svg)](https://github.com/DBHeise/fileid/actions/workflows/analysis.yml)[![Run File Tests](https://github.com/DBHeise/fileid/actions/workflows/test.yml/badge.svg)](https://github.com/DBHeise/fileid/actions/workflows/test.yml)

Like the linux utility "file", this tool will take an arbirtrary file blob and attempt to identify the file type/extension based on magic numbers. In addition it will attempt to pull as much pertinant details as it knows from the file about its format.

It will identify specific formats in container formats. For example it will identify Microsoft Office file types specifically for OLE Structured Storage files (doc, xls, ppt, pub, vsd, etc), and ZIP files (docx, docm, xlsx, xlsm, pptx, pptm, jar, war, xpi, xap, apk,   etc)

## Contributors

[![Contributors](https://contrib.rocks/image?repo=DBHeise/fileid)](https://github.com/DBHeise/fileid/graphs/contributors)

## Binaries

Binaries availabe as artifacts in the [github actions](https://github.com/DBHeise/fileid/actions/workflows/build.yml) and in the [releases](https://github.com/DBHeise/fileid/releases)


Build scripts are included for both gcc/g++ (>=5.1) (via [makefile](https://github.com/DBHeise/fileid/blob/master/makefile)) and Microsoft Visual Studio (>=2015) builds (via [sln](https://github.com/DBHeise/fileid/blob/master/fileid.sln))

## Levels of Coverage

There are three levels of coverage for a file format:

1. **Identification** - we are able to identify the file format from a binary blob, sometimes this is as simple as matching the magic number/bytes, but for many formats it is not as simple
2. **Metadata** - we are able to identify the file format and extract some or all of the associated meta data included in the format. For example, we can tell its an Microsoft Office Binary Document and tell you the specific version of DOC file. This level is further broken down to a rating of how much metadata can be extracted on a scale of 1 to 10 (1 being very basic metadata, 10 be all available meta data fully extracted)
3. **Full Extraction** - we are able to identify pretty much every byte in the file, what it does and why its there.

## File Format Coverage

[File Format Coverage](./coverage.md)

## Usage

```text
fileid {file} [format]
   {file} - required path the file in question
   [format] - optional output format (TEXT [default], CSV, JSON, XML)
```

## Examples

<details>
<summary>Exe with Json Output</summary>

```shell
fileid c:\windows\notepad.exe json
```

```json
{	"name": "C:\\Windows\\notepad.exe",
	"extensions": [
		{ "extension": "exe", "name": "Executable", "machinetype": "x64", "LinkerVersion": "12.10", "OsVersion": "10.0", "ImageVersion": "10.0", "Characteristics": [ "Executable Image","LARGE_ADDRESS_AWARE"]}
	]
}
```

</details>

<details>
<summary>XLS (with vba) with XML Output</summary>

```shell
fileid C:\TestFiles\Sample\Good.macro.xls xml
```

```xml
	<file>
	<name>C:\TestFiles\Sample\Good.macro.xls</name>
	<extensions>
		<item><extension>.xls</extension><version>1536</version><name>BIFF8</name></item>
		<item><extension>.vba</extension><name>Visual Basic for Applications</name><ProjectName>VBAProject</ProjectName><ProjectVersion>136</ProjectVersion><VBAVersionMajor>347260</VBAVersionMajor><VBAVersionMinor>12</VBAVersionMinor><References><Reference>stdole</Reference><Reference>Office</Reference></References><Modules><Module><Name>Module1</Name><StreamName>Module1</StreamName><Offset>1092</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[Attribute VB_Name = "Module1"

Sub Macro1()

Attribute Macro1.VB_Description = "this is macro1"

Attribute Macro1.VB_ProcData.VB_Invoke_Func = " \n14"

'

' Macro1 Macro

' this is macro1

'



'



	 Selection.Font.Bold = True

End Sub

]]></Code></Module>,<Module><Name>ThisWorkbook</Name><StreamName>ThisWorkbook</StreamName><Offset>805</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[Attribute VB_Name = "ThisWorkbook"

Attribute VB_Base = "0{00020819-0000-0000-C000-000000000046}"

Attribute VB_GlobalNameSpace = False

Attribute VB_Creatable = False

Attribute VB_PredeclaredId = True

Attribute VB_Exposed = True

Attribute VB_TemplateDerived = False

Attribute VB_Customizable = True

]]></Code></Module>,<Module><Name>Sheet1</Name><StreamName>Sheet1</StreamName><Offset>805</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[Attribute VB_Name = "Sheet1"

Attribute VB_Base = "0{00020820-0000-0000-C000-000000000046}"

Attribute VB_GlobalNameSpace = False

Attribute VB_Creatable = False

Attribute VB_PredeclaredId = True

Attribute VB_Exposed = True

Attribute VB_TemplateDerived = False

Attribute VB_Customizable = True

]]></Code></Module>,<Module><Name>Sheet2</Name><StreamName>Sheet2</StreamName><Offset>805</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[Attribute VB_Name = "Sheet2"

Attribute VB_Base = "0{00020820-0000-0000-C000-000000000046}"

Attribute VB_GlobalNameSpace = False

Attribute VB_Creatable = False

Attribute VB_PredeclaredId = True

Attribute VB_Exposed = True

Attribute VB_TemplateDerived = False

Attribute VB_Customizable = True

]]></Code></Module>,<Module><Name>Sheet3</Name><StreamName>Sheet3</StreamName><Offset>805</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[Attribute VB_Name = "Sheet3"

Attribute VB_Base = "0{00020820-0000-0000-C000-000000000046}"

Attribute VB_GlobalNameSpace = False

Attribute VB_Creatable = False

Attribute VB_PredeclaredId = True

Attribute VB_Exposed = True

Attribute VB_TemplateDerived = False

Attribute VB_Customizable = True

]]></Code></Module>,<Module><Name></Name><StreamName></StreamName><Offset>0</Offset><isPrivate>0</isPrivate><isReadOnly>0</isReadOnly><Code><![CDATA[]]></Code></Module></Modules></item>
	</extensions>
</file>
```

</details>
