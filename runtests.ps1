gci .\Bin -Recurse -Include *_test.exe  | % { 
. $_ 
if ($LASTEXITCODE) { Write-Warning "Test Failed, exiting"; exit $LASTEXITCODE }
}
$fileIdExe = Resolve-Path .\Bin\x64\Debug\Fileid.exe


pushd ..\fileid.testfiles
$FolderList = @("C:\dev.public\fileid.testfiles", "C:\dev.public\fileid\test\files", "E:\Library.TestFiles")

$FolderList | % {
	$folder = $_
	
	.\Test-Files.ps1 -FileIdExe $fileIdExe -Folder $folder
	if ($LASTEXITCODE) { Write-Warning "Test Failed, exiting"; exit $LASTEXITCODE }
	
	.\Test-XmlOutput.ps1  -FileIdExe $fileIdExe -Folder $folder
	if ($LASTEXITCODE) { Write-Warning "Test Failed, exiting"; exit $LASTEXITCODE }
}

.\Test-ExcelFormulas.ps1 -FileIdExe $fileIdExe

popd
