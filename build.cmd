@echo off
msbuild .\fileid.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x86 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.sln /t:Rebuild /p:Configuration=Release /p:Platform=x86 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64 /nologo /clp:ErrorsOnly;NoSummary
msbuild .\fileid.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64 /nologo /clp:ErrorsOnly;NoSummary
