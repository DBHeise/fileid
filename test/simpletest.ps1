$testFolder = Resolve-Path '.\files'
Set-Alias fileid (Resolve-Path ..\Bin\x64\Debug\fileid.exe)

gci $testFolder -Recurse | ?{!$_.PSIsContainer} | % {
    $r = [String]::Join('',(fileid $_.FullName json)) | ConvertFrom-Json
    $actual = $r.extensions.extension
    $expected = $_.Extension.Trim('.')
    if ($actual -ne $expected) {
        New-Object PSObject -Property @{
            File = $_.FullName
            Expected = $expected
            Actual = $actual
        }
    }
}