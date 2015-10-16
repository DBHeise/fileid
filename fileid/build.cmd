@echo off
msbuild .\fileid.vcxproj /t:Rebuild /p:Configuration=Debug /p:Platform=win32 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform=win32 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.vcxproj /t:Rebuild /p:Configuration=Debug /p:Platform=x64 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform=x64 /nologo /clp:ErrorsOnly;NoSummary
